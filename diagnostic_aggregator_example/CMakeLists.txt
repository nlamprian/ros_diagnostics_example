cmake_minimum_required(VERSION 2.8.3)
project(diagnostic_aggregator_example)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED
  pluginlib
  xmlrpcpp
  roscpp
  diagnostic_msgs
  diagnostic_aggregator
)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    ${PROJECT_NAME}_analyzers
  CATKIN_DEPENDS 
    pluginlib
    xmlrpcpp
    roscpp
    diagnostic_msgs
    diagnostic_aggregator
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

file(GLOB_RECURSE ANALYZER_SRCS src/analyzer/*.cpp)
add_library(${PROJECT_NAME}_analyzers ${ANALYZER_SRCS})
target_link_libraries(${PROJECT_NAME}_analyzers ${catkin_LIBRARIES})
