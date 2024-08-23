#ifndef INSPECTION_MISSION_NODE
#define INSPECTION_MISSION_NODE

#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <cmath>
#include "lart_msgs/msg/dynamics_cmd.hpp"
#include "lart_common/lart_common.h"

#define STEERING_PERIOD_SEC 5.0f
#define MOTOR_SPEED_RPM 10
#define CMD_PUBLISH_PERIOD std::chrono::milliseconds(100)
#define MISSION_DURATION_SEC 26.0


/*! \brief Inspection mission node class. */
class InspectionMission : public rclcpp::Node {

    public:
        /*! \brief Inspection mission controller. Initializes the publisher and timers. */
        InspectionMission();

    private:
        /*! \brief Timer callback for control publishing. */
        void timer_callback();

        /*! \brief Control command publisher. */
        rclcpp::Publisher<lart_msgs::msg::DynamicsCMD>::SharedPtr control_pub;

        /*! \brief Timer. */
        rclcpp::TimerBase::SharedPtr timer;

        /*! \brief Mission start time. */
        rclcpp::Time start_time;

        /*! \brief Flag to denote the mission is finished. */
        bool finished = false;

};

#endif // INSPECTION_MISSION_NODE