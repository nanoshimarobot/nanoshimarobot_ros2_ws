#pragma once

#include <rclcpp/rclcpp.hpp>
#include <chrono>

#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/msg/point_cloud.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/point_cloud_conversion.hpp>
#include <laser_geometry/laser_geometry.hpp>

#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include <cmath>
#include <optional>
#include <algorithm>
#include <random>

namespace nanoshimarobot {
    class LaserscanProcessor : public rclcpp::Node{
        private:
            rclcpp::Publisher<sensor_msgs::msg::PointCloud>::SharedPtr pcl_pub_;
            laser_geometry::LaserProjection converter_;

        public:
            LaserscanProcessor(const rclcpp::NodeOptions &options) : LaserscanProcessor("",options){}
            LaserscanProcessor(const std::string &name_space="", const rclcpp::NodeOptions &options=rclcpp::NodeOptions()):
            Node("laserscan_processor_node",name_space,options)
            {
                using namespace std::chrono_literals;

                pcl_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud>("detected_pcl",rclcpp::QoS(10));

                static auto scan_sub = this->create_subscription<sensor_msgs::msg::LaserScan>(
                    "/scan",
                    rclcpp::QoS(10),
                    [&](const sensor_msgs::msg::LaserScan::SharedPtr msg){
                        sensor_msgs::msg::PointCloud2 cloud2;
                        sensor_msgs::msg::PointCloud cloud;
                        converter_.projectLaser(*msg, cloud2);
                        sensor_msgs::convertPointCloud2ToPointCloud(cloud2, cloud);
                    }
                );
            }

            // void preprocess(sensor_msgs::msg::)
    };
}