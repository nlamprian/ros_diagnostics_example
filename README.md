ros_diagnostics_example
===

A test setup for experimenting and familiarizing oneself with ROS diagnostics.

There are two (randomized) dummy drivers that publish to diagnostics, and two analyzers that respond with messages to error conditions. Read more in the following [post](http://nlamprian.me/blog/software/ros/2018/03/25/ros-diagnostics-continued/).

Use
===

```
roslaunch diagnostic_updater_example updater.launch
roslaunch diagnostic_aggregator_example aggregator.launch
```
