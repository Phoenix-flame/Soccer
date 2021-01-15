#include <Network/GrSim.h>
#include <Core/Log.h>
#include <../build/grSim_Packet.pb.h>
namespace Phoenix{
    GrSim::GrSim(){
        PHX_CORE_TRACE("HERE");
        m_Sock = CreateRef<UDPSocket>();
        // m_Sock->joinGroup("127.0.0.1");
        PHX_CORE_TRACE("HERE");
    }
    

    void GrSim::InitPosition(){
        grSim_Packet packet;
        for (unsigned int i = 0 ; i < 8 ; i++){
            grSim_RobotReplacement* r_pos = packet.mutable_replacement()->add_robots();
            r_pos->set_id(i);
            r_pos->set_yellowteam(true);
            r_pos->set_dir(0.0);
            if (i == 3){
                r_pos->set_x(1);
                r_pos->set_y(0);
                r_pos->turnon();
                continue;
            }
            r_pos->set_x(0.5 + 0.3*i);
            r_pos->set_y(-3.5);
            r_pos->set_turnon(false);
        }
        for (unsigned int i = 0 ; i < 8 ; i++){
            grSim_RobotReplacement* r_pos = packet.mutable_replacement()->add_robots();
            r_pos->set_id(i);
            r_pos->set_yellowteam(false);
            r_pos->set_dir(0.0);
            if (i == 3){
                r_pos->set_x(-1);
                r_pos->set_y(0);
                r_pos->turnon();
                continue;
            }
            r_pos->set_x(-0.5 - 0.3*i);
            r_pos->set_y(-3.5);
            r_pos->set_turnon(false);
        }
        std::string content;
        packet.SerializeToArray(s_OutgoingArray, packet.ByteSize());
        try{
            m_Sock->sendTo(s_OutgoingArray, packet.ByteSize(), "127.0.0.1", 20011);
        }catch(std::exception const& e){
            PHX_CORE_CRITICAL(e.what());
        }
    }

}