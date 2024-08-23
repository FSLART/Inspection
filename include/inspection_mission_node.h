#ifndef INSPECTION_MISSION_NODE
#define INSPECTION_MISSION_NODE

#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <cmath>
#include <lart_msgs/msg/dynamics_cmd.hpp>
#include "lart_common/lart_common.h"

/*! \brief Inspection mission node class. */
class InspectionMission : public rclcpp::Node {

    public:
        /*! \brief Inspection mission controller. Initializes the publisher and timers. */
        InspectionMission();

    private:
        /*! \brief Timer callback for control publishing. */
        void timer_callback();

        /*! \brief Control command publisher. */
        rclcpp::Publisher<lart_msgs::msg::DynamicsCMD>::SharedPtr control_pub_;

        /*! \brief Timer. */
        rclcpp::TimerBase::SharedPtr timer;

        /*! \brief Mission start time. */
        std::time_t start_time;

        /*! \brief Flag to denote the mission is finished. */
        bool finished;

};

#endif // INSPECTION_MISSION_NODE