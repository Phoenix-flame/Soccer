#include <Vision/Vision.h>
#include <Core/Log.h>
#include <Core/Config.h>
namespace Phoenix{
    Vision* Vision::s_Instance = nullptr;
    Vision::Vision(){
        s_Instance = this;
        m_Sock = CreateRef<UDPSocket>(Config::s_VisionConfig.port);
        PHX_CORE_TRACE("IP: {0}, Port: {1}", Config::s_VisionConfig.ip, Config::s_VisionConfig.port);
        Connect();
    }
    Vision::~Vision(){
        m_Sock->leaveGroup(Config::s_VisionConfig.ip);
    }

    void Vision::Connect(){
        try{
            m_Sock->joinGroup(Config::s_VisionConfig.ip);
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