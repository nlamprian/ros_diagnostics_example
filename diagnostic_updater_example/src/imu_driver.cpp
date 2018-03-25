#include "diagnostic_updater_example/imu_driver.h"

using namespace diagnostic_updater;

ImuDriver::ImuDriver()
    : random_device_(),
      random_generator_(random_device_()),
      normal_time_distribution_(0, 0.35),
      normal_freq_distribution_(0, 5.00),
      freq_(20),
      min_freq_(freq_ - 2),
      max_freq_(freq_ + 2) {
  state_period_ = ros::Duration(4);
}

void ImuDriver::init(ros::NodeHandle &nh, Updater &updater) {
  ros::Publisher data_publisher = nh.advertise<sensor_msgs::Imu>("imu", 10);
  data_diagnosed_publisher_ =
      std::make_shared<DiagnosedPublisher<sensor_msgs::Imu>>(
          data_publisher, updater,
          FrequencyStatusParam(&min_freq_, &max_freq_, 0.02, 10),
          TimeStampStatusParam(-1.0, 1.0));

  DriverBase::init(nh, updater);
}

void ImuDriver::execLoop() {
  while (!terminating_) {
    std::unique_lock<std::mutex> lock(exec_mutex_);

    // Update data
    ros::Duration time_offset(normal_time_distribution_(random_generator_));
    data_.header.stamp = ros::Time::now() + time_offset;
    data_diagnosed_publisher_->publish(data_);

    updateState();

    double freq = freq_ + normal_freq_distribution_(random_generator_);
    exec_cv_.wait_for(lock,
                      std::chrono::milliseconds(static_cast<int>(1000 / freq)),
                      [&] { return terminating_.load(); });
  }
}
