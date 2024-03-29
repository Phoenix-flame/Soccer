#pragma once 
#include <chrono>
#include <string>
#include <Core/Log.h>
#include <Network/Debugger.h>


namespace Phoenix{
    class ScopeTimer{
    public:
        ScopeTimer(std::string name){
            m_Time = std::chrono::high_resolution_clock::now();
            m_Name = name;
        }
        ~ScopeTimer(){
            auto end = std::chrono::high_resolution_clock::now();
            int duration = std::chrono::duration_cast<std::chrono::microseconds>(end - m_Time).count();
            // PHX_CORE_WARN("{0}: {1} us", m_Name, duration);
            Debugger::AddTimeProfile(m_Name, duration);
        }
        ScopeTimer(const ScopeTimer&) = delete;
        ScopeTimer& operator=(const ScopeTimer&) = delete;
    
    private:
        typedef std::chrono::system_clock::time_point time_point;
        time_point m_Time;
        std::string m_Name;
    };
}
#define PHX_SCOPE_TIMER(name) Phoenix::ScopeTimer t(name);