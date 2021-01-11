#include <Vision/Vision.h>
#include <Core/Log.h>
#include <Core/Config.h>
#include <math.h>
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
            int incoming_size = m_Sock->recv(incoming_buffer, MAX_INCOMING_PACKET_SIZE);
            packet.ParseFromArray(incoming_buffer, incoming_size);
        }
        catch(std::exception const& e){
            throw std::runtime_error("vision error");
        }
        if (packet.has_detection()){
            frame[packet.detection().camera_id()] = packet.detection();
            packet_recieved[packet.detection().camera_id ()] = true;
        }
        ProcessRobots();
    }


    void Vision::ProcessRobots(){
        int yellow_robots = ExtractYellowTeam();
        PHX_CORE_WARN("---------------------------------------");
        for (unsigned int i = 0 ; i <yellow_robots ; i++){
            PHX_CORE_TRACE("{0}:\t position:[{1},\t {2}\t], orientation:\t{3}", robot[i].robot_id(), round(robot[i].x()), round(robot[i].y()), robot[i].orientation());
        }
    }
    int Vision::ExtractYellowTeam(){
        int ans = 0;
        for (int i = 0; i < CAM_COUNT; i++){
            if ( Config::s_VisionConfig.enabled_cam[i] ){
                for ( int j = 0 ; j < min(MAX_ROBOTS, frame[i].robots_yellow_size()) ; j ++ ){
                    robot[ans] = frame[i].robots_yellow(j);
                    ans++;
                }
            }
        }
        return ans;
    }
    int Vision::ExtractBlueTeam(){
        return 0;
    }
}