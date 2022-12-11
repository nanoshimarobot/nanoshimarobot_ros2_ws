from ast import arguments
from http.server import executable
import os
from struct import pack
from tkinter.font import names
from matplotlib import container
import yaml
import launch
import datetime
from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch.actions import IncludeLaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import ComposableNodeContainer
from launch_ros.actions import Node
from launch_ros.descriptions import ComposableNode

robot_ns = "nanoshimarobot"

def generate_launch_description():
    pkg_dir = get_package_share_directory("nanoshimarobot_bringup")
    list = [
        Node(
            package='rviz2',
            namespace='',
            executable='rviz2',
            name='rviz2',
            # output=
            # arguments=['-d' + os.path.join(pkg_dir, "rviz", rviz_config)],
        ),

        DeclareLaunchArgument(
            name='serial_port', 
            default_value='',
            description='LD06 Serial Port'
        ),
        DeclareLaunchArgument(
            name='topic_name', 
            default_value='scan',
            description='LD06 Topic Name'
        ),
        DeclareLaunchArgument(
            name='lidar_frame', 
            default_value='laser',
            description='Lidar Frame ID'
        ),
        DeclareLaunchArgument(
            name='range_threshold', 
            default_value='0.005',
            description='Range Threshold'
        ),
        Node(
            package='ldlidar',
            executable='ldlidar',
            name='ldlidar',
            output='screen',
            parameters=[
                {'serial_port': LaunchConfiguration("serial_port")},
                {'topic_name': LaunchConfiguration("topic_name")},
                {'lidar_frame': LaunchConfiguration("lidar_frame")},
                {'range_threshold': LaunchConfiguration("range_threshold")}
            ]
        )
    ]

    return LaunchDescription(list)