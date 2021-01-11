#include <Core/EditorLayer.h>
#include <Phoenix/core/log.h>
#include <Phoenix/core/base.h>
#include <Phoenix/event/event.h>
#include <Phoenix/imGui/imgui_internal.h>
#include <Phoenix/Scene/Component.h>
#include <Phoenix/core/Profiler.h>
#include <Phoenix/core/Input.h>
#include <Phoenix/Math/Math.h>

namespace ssl{
    EditorLayer::EditorLayer(const std::string& name): Layer(name), 
        m_MainCamera()
    { }

    void EditorLayer::OnAttach() {
        PHX_INFO("{0} attached.", this->layer_name);

        Application::Get().GetWindow().SetVSync(true);

        FramebufferSpecification fbSpec;
        fbSpec.Width = 640;
        fbSpec.Height = 480;
        m_Framebuffer = Framebuffer::Create(fbSpec);

        m_Scene = CreateRef<Phoenix::Scene>();

        m_Scene->OnResize(m_Framebuffer->GetSpecification().Width, m_Framebuffer->GetSpecification().Height);

    }

    void EditorLayer::OnDetach() {
        PHX_INFO("{0} detached.", this->layer_name);
    }

    void EditorLayer::OnUpdate(Phoenix::Timestep ts) {
        Phoenix::RenderCommand::SetClearColor(glm::vec4(0.0, 0.0, 0.0, 1.0));
        Phoenix::RenderCommand::Clear();

        FramebufferSpecification spec = m_Framebuffer->GetSpecification();
        if ( m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
            (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)){
            m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_Scene->OnResize(m_ViewportSize.x, m_ViewportSize.y);
            m_MainCamera.OnResize(m_ViewportSize.x, m_ViewportSize.y);
        }

        // Update
        if (m_ViewportFocused){
            m_MainCamera.OnUpdate(ts);
        }

        m_Framebuffer->Bind();

        Phoenix::RenderCommand::SetClearColor(glm::vec4(m_BackgroundColor, 1.0));
        Phoenix::RenderCommand::Clear();
        
        glm::mat4 projection = m_MainCamera.GetViewProjectionMatrix();
        {
            m_Scene->OnUpdate(m_MainCamera, ts);
        }

        m_Framebuffer->Unbind();
    }


    void EditorLayer::OnEvent(Phoenix::Event& e) {
        if (m_ViewportFocused){
            m_MainCamera.OnEvent(e);
        }
        
        EventDispatcher dispacher(e);
        dispacher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(EditorLayer::OnResize));
        dispacher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(EditorLayer::OnKeyPressed));
        dispacher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e){
            if (e.GetKeyCode() == Phoenix::Key::Escape){
                Phoenix::Application::Get().Close();
                return true;
            }
            return false;
        });
    }


    void EditorLayer::OnImGuiRender(){
        ImGui::Begin("Settings", nullptr, (ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize) & ImGuiWindowFlags_None);
        ImGui::Text("Metrics");
        ImGuiContext& g = *GImGui;
        ImGuiIO& io = g.IO;
        ImGuiMetricsConfig* cfg = &g.DebugMetricsConfig;

        // Basic info
        ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);
        ImGui::Separator();

        ImGui::ColorEdit3("Background Color", glm::value_ptr(m_BackgroundColor));
        if (ImGui::Checkbox("VSync", &vsync)){
            Application::Get().GetWindow().SetVSync(vsync);
        }
        ImGui::End();

        ImGui::Begin("Profiler", nullptr, (ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize) & ImGuiWindowFlags_None);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
        ImGui::Columns(2);
        ImGui::Separator();
        int id = 0;
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
        for (auto p:Application::s_TimeContainer){
            ImGui::PushID(id++);
            ImGui::AlignTextToFramePadding();
            ImGui::Text((p.first).c_str());
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(-1);
            ImGui::Text((std::to_string(p.second) + " us").c_str());
            ImGui::NextColumn();
            ImGui::PopID();
        }
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::PopStyleVar();
        ImGui::End();


        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        
        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });


        ImGui::End();
        ImGui::PopStyleVar();
    }



    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e){
        // Shortcuts
        if (e.GetRepeatCount() > 0)
            return false;

        bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
        bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
        switch (e.GetKeyCode()){
            
        }
        return false;
    }
}