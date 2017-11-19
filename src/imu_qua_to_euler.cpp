#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <sensor_msgs/Imu.h>
#include <string>
#include <math.h>

using namespace std;
#define CLAMP(x , min , max) ((x) > (max) ? (max) : ((x) < (min) ? (min) : x))

void imuCallback(const sensor_msgs::Imu &imumsg)
{
    double m_fRoll,m_fPitch,m_fYaw;

        /// Cartesian coordinate System 

    m_fRoll  = atan2(2 * (w * z + x * y) , 1 - 2 * (z * z + x * x));
    m_fPitch = asin(CLAMP(2 * (w * x - y * z) , -1.0f , 1.0f));
    m_fYaw   = atan2(2 * (w * y + z * x) , 1 - 2 * (x * x + y * y));

    ROS_INFO("Roll = %f ", m_fRoll);
    ROS_INFO("Pitch = %f ", m_fPitch);
    ROS_INFO("Yaw = %f ", m_fYaw);
}

int main(int argc, char ** argv)
{

    ros::init(argc, argv,"imu_qua_to_euler");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/raw_imu",5,imuCallback);
    
    ros::spin();

    return 0;
}

