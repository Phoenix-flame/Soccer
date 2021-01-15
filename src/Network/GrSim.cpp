#include <Network/GrSim.h>
#include <Core/Log.h>

namespace Phoenix{
    GrSim::GrSim(){
        m_Sock = CreateRef<UDPSocket>();
        m_CommandPacket = CreateRef<grSim_Packet>();
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
        packet.SerializeToArray(m_OutgoingArray, packet.ByteSize());
        try{
            m_Sock->sendTo(m_OutgoingArray, packet.ByteSize(), "127.0.0.1", 20011);
        }catch(std::exception const& e){
            PHX_CORE_CRITICAL(e.what());
        }
    }


    void GrSim::SendCommand(const GrSimCommand& c){
        m_CommandPacket->mutable_commands()->set_isteamyellow(true);
        m_CommandPacket->mutable_commands()->set_timestamp(0.0);
        grSim_Robot_Command* comm = m_CommandPacket->mutable_commands()->add_robot_commands();
        comm->set_id(c.id);
        comm->set_velangular(c.w_vel);
        comm->set_velnormal(c.y_vel);
        comm->set_veltangent(c.x_vel);
        comm->set_kickspeedx(c.kick);
        comm->set_kickspeedz(c.chip);
        comm->set_spinner(0.0);
        comm->set_wheel1(0.0);
        comm->set_wheel2(0.0);
        comm->set_wheel3(0.0);
        comm->set_wheel4(0.0);
        comm->set_wheelsspeed(0.0);
    }

    void GrSim::FlushCommands(){
        
        std::string content;
        m_CommandPacket->SerializeToArray(m_OutgoingArray, m_CommandPacket->ByteSize());
        try{
            m_Sock->sendTo(m_OutgoingArray, m_CommandPacket->ByteSize(), "127.0.0.1", 20011);
        }catch(std::exception const& e){
            PHX_CORE_CRITICAL(e.what());
        }
        m_CommandPacket->Clear();
    }

}