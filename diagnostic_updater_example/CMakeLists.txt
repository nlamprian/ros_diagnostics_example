cmake_minimum_required(VERSION 2.8.3)
project(diagnostic_updater_example)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  diagnostic_updater
  roscpp
  rospy
)

catkin_package()

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_imu_driver src/imu_driver.cpp src/imu_driver_node.cpp)
set_target_properties(${PROJECT_NAME}_imu_driver PROPERTIES OUTPUT_NAME imu_node PREFIX "")
target_link_libraries(${PROJECT_NAME}_imu_driver ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_gps_driver src/gps_driver.cpp src/gps_driver_node.cpp)
set_target_properties(${PROJECT_NAME}_gps_driver PROPERTIES OUTPUT_NAME gps_node PREFIX "")
target_link_libraries(${PROJECT_NAME}_gps_driver ${catkin_LIBRARIES})
