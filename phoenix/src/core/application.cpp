#include "Phoenix/core/application.h"
#include <Phoenix/renderer/renderer.h>
#include <Phoenix/renderer/renderer_command.h>

namespace Phoenix{
    Application* Application::s_Instance = nullptr;

    std::map<std::string, int> Application::s_TimeContainer;
    Application::Application(const std::string name) {
        m_Name = name;

        PHX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
        m_Window = std::make_unique<Window>(WindowProperties(m_Name));
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        
        Renderer::Init();
        RenderCommand::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
        
        m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

        PHX_CORE_INFO("Application initialized successfully.");
    }

    Application::~Application(){
        Renderer::Shutdown();
    }

    void Application::OnEvent(Event& e){
        EventDispatcher dispathcer(e);
        dispathcer.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
        dispathcer.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it){
			if (e.Handled) 
				break;
			(*it)->OnEvent(e);
		}
    }

    void Application::PushLayer(Layer* layer){
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer){
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close(){
		m_Running = false;
	}


    void Application::Run(){
        while(this->m_Running){
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;


            if (!this->_minimized){
                {
                    for (Layer* layer : m_LayerStack){
                        layer->OnUpdate(timestep);
                    }  
                }

                m_ImGuiLayer->Begin();
                {
                    for (Layer* layer : m_LayerStack){
                        layer->OnImGuiRender();
                    }
                }
                m_ImGuiLayer->End();
            }

            m_Window->OnUpdate();
        }   
    }


    bool Application::OnWindowClose(WindowCloseEvent& e){
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e){
        if (e.GetWidth() == 0 || e.GetHeight() == 0){
            _minimized = true;
            return false;
        }

        _minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }
}