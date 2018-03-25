#ifndef DRIVER_BASE_H
#define DRIVER_BASE_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <ros/ros.h>
#include "diagnostic_updater_example/diagnostic_tasks.h"

class DriverBase {
 public:
  DriverBase()
      : terminating_(false),
        state_period_(1),
        state_(true),
        state_task_(state_),
        next_time_(ros::Time::now()) {}

  virtual ~DriverBase() {
    terminating_ = true;
    exec_cv_.notify_one();
    if (exec_thread_.joinable()) exec_thread_.join();
  }

  virtual void init(ros::NodeHandle & /*nh*/,
                    diagnostic_updater::Updater &updater) {
    updater.add(state_task_);

    exec_thread_ = std::thread(&DriverBase::execLoop, this);
  }

 protected:
  virtual void execLoop() = 0;

  void updateState() {
    if (ros::Time::now() > next_time_) {
      next_time_ = ros::Time::now() + state_period_;
      state_ = !state_;
      state_task_.setState(state_);
    }
  }

  std::mutex exec_mutex_;
  std::condition_variable exec_cv_;
  std::atomic_bool terminating_;

  ros::Duration state_period_;

 private:
  std::thread exec_thread_;

  bool state_;
  StateTask state_task_;
  ros::Time next_time_;
};

#endif  // DRIVER_BASE_H
