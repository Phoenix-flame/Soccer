#pragma once

#include <Phoenix/core/application.h>
#include <Phoenix/core/log.h>
#include <Vision/Vision.h>
#include <Core/Config.h>
#include <Core/EditorLayer.h>
#include <thread>

namespace ssl{
    class MyClient: public Phoenix::Application{
    public:
        MyClient() : Phoenix::Application("SSL Client"){
            PHX_CORE_INFO("Let's Rock");
            
            PushLayer(new EditorLayer("Debugger"));
            
            m_Config = CreateRef<Config>();
            m_Vision = CreateRef<Vision>();
        

            std::thread t1(&MyClient::RunSSL, this);
            t1.detach();            
        }
        void RunSSL();
    private:
        Ref<Vision> m_Vision;
        Ref<Config> m_Config;
    };
}