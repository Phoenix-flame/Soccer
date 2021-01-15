#pragma once
#include <Network/PracticalSocket.h>
#include <Core/Base.h>
#include <../build/grSim_Packet.pb.h>

struct GrSimCommand{
    unsigned int id;
    double x_vel = 0.0;
    double y_vel = 0.0;
    double w_vel = 0.0;
    double kick  = 0.0;
    double chip  = 0.0;
};


namespace Phoenix{
    class GrSim{
    public:
        GrSim();
        void InitPosition();
        void SendCommand(const GrSimCommand& c);
        void FlushCommands();

    private:
        Ref<UDPSocket> m_Sock; 
        Ref<grSim_Packet> m_CommandPacket;
        char s_OutgoingArray[1000];
    };
}