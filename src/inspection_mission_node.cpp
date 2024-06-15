#include <chrono>
#include <cmath>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class InspectionMission : public rclcpp::Node
{
public:
  InspectionMission()
  : Node("inspection_mission_node"),
    start_time_(this->now()),
    finished_(false)
  {
    // criar os publishers
    drivetrain_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("drivetrain_cmd", 10);
    steering_pub_ = this->create_publisher<std_msgs::msg::Float64>("steering_cmd", 10);

    timer_ = this->create_wall_timer(
      100ms, std::bind(&InspectionMission::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto current_time = this->now();
    auto elapsed_time = (current_time - start_time_).seconds();

    if (!finished_) {
      // drivetrain
      auto drivetrain_cmd = geometry_msgs::msg::Twist();
      drivetrain_cmd.linear.x = 0.1;  // rodar devagar
      drivetrain_pub_->publish(drivetrain_cmd);
      RCLCPP_INFO(this->get_logger(), "Published drivetrain command");

      // steering
      auto steering_cmd = std_msgs::msg::Float64();
      steering_cmd.data = 0.5 * std::sin(0.2 * elapsed_time);  // sine wave com periodo de 10s
      steering_pub_->publish(steering_cmd);
      RCLCPP_INFO(this->get_logger(), "Published steering command");

      if (elapsed_time >= 25.0 && elapsed_time <= 30.0) {
        finished_ = true;
        RCLCPP_INFO(this->get_logger(), "AS Finished");

        drivetrain_pub_->publish(geometry_msgs::msg::Twist());  // parar drivetrain
        RCLCPP_INFO(this->get_logger(), "Published stop drivetrain command");

        steering_pub_->publish(std_msgs::msg::Float64());  // centrar steering
        RCLCPP_INFO(this->get_logger(), "Published center steering command");
        
        std::exit(0);
      }
    }
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr drivetrain_pub_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr steering_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Time start_time_;
  bool finished_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<InspectionMission>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
