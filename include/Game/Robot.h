#pragma once

#include <eigen3/Eigen/Eigen>
#include <Core/Log.h>
#include <Network/Debugger.h>
namespace Phoenix{
    class Vision;
    class Robot{
    public:
        Robot(int id): m_Id(id) {}
        ~Robot() = default;

        int GetId() { return m_Id; }

        void Debug(){
            Debugger::AddFloat("Position x", m_Position.x());
            Debugger::AddFloat("Position y", m_Position.y());
            PHX_CORE_TRACE("{0}:\t position:[{1},\t {2}\t], orientation:\t{3}", m_Id, m_Position.x(), m_Position.y(), m_Orientation);
        }
        
    private:
        unsigned int m_Id;
        Eigen::Vector2f m_Position;
        Eigen::Vector2f m_Velocity;
        float m_Orientation;

    private:
        void VisionUpdate(const Eigen::Vector2f& pos, float orientation);
    private:
        friend class Vision;
    };
}