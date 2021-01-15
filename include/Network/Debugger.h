#pragma once
#include <Network/PracticalSocket.h>
#include <Core/Base.h>
#include <../build/aidebug.pb.h>

namespace Phoenix{
    class Debugger{
    public:
        Debugger();
        Debugger(const Debugger& other) = delete;
        Debugger& operator=(const Debugger& other) = default;
        
        static void AddFloat(std::string name, float value);
        static void AddTimeProfile(std::string name, int value);
        static void Flush();
    private:
        static Ref<UDPSocket> s_Sock;
        static AI_Debug s_Packet;
        static char s_OutgoingArray[1000];
    };


}