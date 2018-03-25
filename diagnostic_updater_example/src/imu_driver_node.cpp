#include "diagnostic_updater_example/imu_driver.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "imu_driver");
  ros::NodeHandle nh;

  diagnostic_updater::Updater updater;
  updater.setHardwareID("IMU");

  ImuDriver driver;
  driver.init(nh, updater);

  ros::Rate rate(50);
  while (nh.ok()) {
    updater.update();
    rate.sleep();
  }

  return 0;
}
