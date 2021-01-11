#include <Vision/Vision.h>
#include <Core/Log.h>

namespace Phoenix{
    Vision* Vision::s_Instance = nullptr;
    Vision::Vision(){
        s_Instance = this;
        m_Sock = CreateRef<UDPSocket>(10020);
        Connect();
    }
    Vision::~Vision(){
        m_Sock->leaveGroup("224.5.23.2");
    }

    void Vision::Connect(){
        try{
            m_Sock->joinGroup("224.5.23.2");
            m_Connected = true;
        }catch(std::exception const& e){
            PHX_CORE_CRITICAL("Vision is not AVAILABLE!");
        }
        
    }

    void Vision::ReceivePacket(){
        if (!m_Connected) throw std::runtime_error("vision error");

        try{
            int incoming_size = m_Sock->recv(incoming_buffer , MAX_INCOMING_PACKET_SIZE);
            PHX_CORE_TRACE("PACKET SIZE: {0}", incoming_size);
            // packet.ParseFromArray(incoming_buffer,incoming_size);
        }
        catch(std::exception const& e){
            throw std::runtime_error("vision error");
        }
    }
}