#pragma once
#include <Network/PracticalSocket.h>
#include <Core/Base.h>
#include <../build/aidebug.pb.h>

namespace Phoenix{
    class Debugger{
    public:
        Debugger(){
            s_Sock = CreateRef<UDPSocket>(10007);
            s_Sock->joinGroup("224.5.23.16");
        }
        static void AddFloat(std::string name, float value);
        static void Flush();
    private:
        static Ref<UDPSocket> s_Sock;
        static AI_Debug s_Packet;
        static char s_OutgoingArray[1000];
    };


}