#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H

#include <memory>
#include <random>

#include <diagnostic_updater/publisher.h>
#include <sensor_msgs/Imu.h>
#include "diagnostic_updater_example/driver_base.h"

class ImuDriver : public DriverBase {
  template <typename T>
  using DiagnosedPublisherPtr =
      std::shared_ptr<diagnostic_updater::DiagnosedPublisher<T>>;

 public:
  ImuDriver();
  virtual void init(ros::NodeHandle &nh,
                    diagnostic_updater::Updater &updater) override;

 private:
  virtual void execLoop() override;

  std::random_device random_device_;
  std::mt19937 random_generator_;
  std::normal_distribution<> normal_time_distribution_;
  std::normal_distribution<> normal_freq_distribution_;

  sensor_msgs::Imu data_;
  double freq_, min_freq_, max_freq_;
  DiagnosedPublisherPtr<sensor_msgs::Imu> data_diagnosed_publisher_;
};

#endif  // IMU_DRIVER_H
