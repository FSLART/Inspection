#include "inspection_mission_node.h"

InspectionMission::InspectionMission() : Node("inspection_mission_node") {

    // get the current time
    this->start_time = this->now();

    // create the publisher
    this->control_pub = this->create_publisher<lart_msgs::msg::DynamicsCMD>("/cmd", 10);

    // create a timer bound to the timer callback every 100ms
    this->timer = this->create_wall_timer(CMD_PUBLISH_PERIOD, std::bind(&InspectionMission::timer_callback, this));

    // initialize the finished flag to false
    this->finished = false;

}

void InspectionMission::timer_callback() {

    // get the current time
    rclcpp::Time current_time = this->now();

    // calculate the elapsed time
    rclcpp::Duration elapsed_time_dur = this->start_time - current_time;
    float elapsed_time = elapsed_time_dur.seconds(); 

    // if the total elapsed time has passed, shut the node down
    if(elapsed_time > MISSION_DURATION_SEC) {
        rclcpp::shutdown();
    }

    // calculate the steering angle based on the current time
    float st_angle_cur = MAX_STEERING_ANGLE_RAD * std::sin(((2.0f*LART_PI)/STEERING_PERIOD_SEC)*elapsed_time);

    // initialize the control message
    lart_msgs::msg::DynamicsCMD cmd = lart_msgs::msg::DynamicsCMD();
    cmd.steering_angle = st_angle_cur;
    cmd.rpm = (std::uint16_t) MOTOR_SPEED_RPM;

    // publish the control message
    this->control_pub->publish(cmd);
}
