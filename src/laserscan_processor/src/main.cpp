#include <rclcpp/rclcpp.hpp>
#include "../include/laserscan_processor/laserscan_processor_component.hpp"

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<nanoshimarobot::LaserscanProcessor>());
    rclcpp::shutdown();
    return 0;
}