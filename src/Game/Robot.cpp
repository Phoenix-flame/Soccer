#include <Game/Robot.h>


namespace Phoenix{
    Robot::Robot(int id): m_Id(id) {
        int n = 4; // Number of states
        int m = 2; // Number of measurements

        double dt = 1.0/60; // Time step

        Eigen::MatrixXd A(n, n); // System dynamics matrix
        Eigen::MatrixXd C(m, n); // Output matrix
        Eigen::MatrixXd Q(n, n); // Process noise covariance
        Eigen::MatrixXd R(m, m); // Measurement noise covariance
        Eigen::MatrixXd P(n, n); // Estimate error covariance

        A <<    1, 0, dt,  0, 
                0, 1,  0, dt, 
                0, 0,  1,  0, 
                0, 0,  0,  1;
        C <<  1, 0, 0, 0, 
              0, 1, 0, 0;

        Q <<    1, .0, .0, .0, 
                .0, 1, .0, .0, 
                .0, .0, 1, .0, 
                .0, .0, .0, 1;
        R <<    5, 0, 
                0, 5;
        P <<  1,    .0,  .0, .0, 
             .0,     1,  .0, .0, 
             .0,    .0,   100, .0, 
             .0,    .0,  .0,  100;

        m_Filter = CreateRef<KalmanFilter>(dt, A, C, Q, R, P);
        m_Filter->init();
    }
    void Robot::VisionUpdate(const Eigen::Vector2f& pos, float orientation){
        m_Position = pos;
        m_Orientation = orientation;
    }

    void Robot::UpdateKalman(double dt, const Eigen::VectorXd& measurment){
        Eigen::MatrixXd A(4, 4);
        A << 1, 0, dt,  0, 
             0, 1,  0, dt, 
             0, 0,  1,  0, 
             0, 0,  0,  1;
        m_Filter->update(measurment, dt, A);
        Eigen::MatrixXd convert(2, 4);
        convert << 0, 0, -1/230.0, 0, 0, 0, 0, -1/230.0;
        Eigen::VectorXd velocity = convert*m_Filter->state(); 
        Debugger::AddFloat("Velocity x", velocity.x());
        Debugger::AddFloat("Velocity y", velocity.y());
    }
}