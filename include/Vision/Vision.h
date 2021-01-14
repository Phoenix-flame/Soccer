#pragma once

#include <Network/PracticalSocket.h>
#include <Core/Base.h>
#include <../build/messages_robocup_ssl_detection.pb.h>
#include <../build/messages_robocup_ssl_wrapper.pb.h>

#define MAX_INCOMING_PACKET_SIZE 1000
#define CAM_COUNT 4
#define MAX_BALLS 10
#define MAX_BALL_NOT_SEEN 40

#define MAX_ROBOT_NOT_SEEN 600
#define MAX_ROBOT_SUBSITUTE 60
#define MAX_ROBOTS 60

namespace Phoenix{
    class Vision{
    public:
        Vision();
        ~Vision();

        void Connect();
        void ReceivePacket();
        operator bool() { return m_Connected; }

    private:
        void ProcessRobots(double dt);
        int ExtractYellowTeam();
        int ExtractBlueTeam();

    private:
        Ref<UDPSocket> m_Sock;
        bool m_Connected = false;

        char incoming_buffer[MAX_INCOMING_PACKET_SIZE];
        SSL_WrapperPacket packet;
		SSL_DetectionFrame frame[CAM_COUNT];
		SSL_DetectionBall d_ball[MAX_BALLS*CAM_COUNT];
        std::map<int, SSL_DetectionRobot> m_YellowRobots;
        std::map<int, SSL_DetectionRobot> m_BlueRobots;
        bool packet_recieved[CAM_COUNT];
        std::map<int, double> m_Timestamp;
        static Vision* s_Instance;
    };
}