#pragma once

#include <Network/PracticalSocket.h>
#include <Core/Base.h>

#define MAX_INCOMING_PACKET_SIZE 1000

namespace Phoenix{
    class Vision{
    public:
        Vision();
        ~Vision();

        void Connect();
        void ReceivePacket();
        operator bool() { return m_Connected; }
    private:
        Ref<UDPSocket> m_Sock;
        bool m_Connected = false;

        char incoming_buffer[MAX_INCOMING_PACKET_SIZE];

        static Vision* s_Instance;
    };
}