#include <Vision/Vision.h>
#include <Core/Log.h>
#include <Core/Config.h>
#include <math.h>
#include <Game/Game.h>
#include <map>
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
        double dt;
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
            dt = packet.detection().t_capture() - m_Timestamp[packet.detection().camera_id()];
            m_Timestamp[packet.detection().camera_id()] = packet.detection().t_capture();
            // PHX_CORE_TRACE("Camera:{0} -> {1} s", packet.detection().camera_id(), dt);
        }
        ProcessRobots(dt);

    }


    void Vision::ProcessRobots(double dt){
        int yellow_robots = ExtractYellowTeam();
        int blue_robots = ExtractBlueTeam();
        Eigen::VectorXd y(2);
        y << (int)m_YellowRobots[3].x(), (int)m_YellowRobots[3].y();
        Game::ourGK->UpdateKalman(dt, y);
        Game::ourGK->VisionUpdate(Eigen::Vector2f(m_YellowRobots[3].x(), m_YellowRobots[3].y()), m_YellowRobots[3].orientation());
    }
    int Vision::ExtractYellowTeam(){
        int ans = 0;
        for (int i = 0; i < CAM_COUNT; i++){
            if (Config::s_VisionConfig.enabled_cam[i] ){
                for (int j = 0 ; j < min(MAX_ROBOTS, frame[i].robots_yellow_size()); j ++){
                    m_YellowRobots[frame[i].robots_yellow(j).robot_id()] = frame[i].robots_yellow(j);
                    ans++;
                }
            }
        }
        return ans;
    }
    int Vision::ExtractBlueTeam(){
        int ans = 0;
        for (int i = 0; i < CAM_COUNT; i++){
            if (Config::s_VisionConfig.enabled_cam[i] ){
                for (int j = 0 ; j < min(MAX_ROBOTS, frame[i].robots_blue_size()); j ++){
                    m_BlueRobots[frame[i].robots_blue(j).robot_id()] = frame[i].robots_blue(j);
                    ans++;
                }
            }
        }
        return ans;
    }
}