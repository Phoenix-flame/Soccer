#include <Game/Robot.h>


namespace Phoenix{
    void Robot::VisionUpdate(const Eigen::Vector2f& pos, float orientation){
        m_Position = pos;
        m_Orientation = orientation;
    }
}