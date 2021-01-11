#ifndef __APPLICATION__
#define __APPLICATION__

#include <Phoenix/imGui/ImGuiLayer.h>
#include <string>
#include <map>
#include "window.h"
#include "base.h"
#include "layerStack.h"
#include "timestep.h"
#include "log.h"
#include "assert.h"

int main(int argc, char** argv);
namespace Phoenix{
    class Application{
    public:
        Application(const std::string name = "Phoenix_flame");
        virtual ~Application();
        void OnEvent(Event&);
        void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
        static Application& Get() { return *s_Instance; }
        static std::map<std::string, int> s_TimeContainer;
    private:
        void Run();
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        std::string m_Name;
        bool _minimized = false;
        bool m_Running = true;
        float m_LastFrameTime = 0.0f;
        std::unique_ptr<Window> m_Window;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;

    private:
        
        static Application* s_Instance;
        friend int ::main(int argc, char** argv);
        
    };
}


#endif