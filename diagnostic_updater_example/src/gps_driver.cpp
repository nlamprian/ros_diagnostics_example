#include "diagnostic_updater_example/gps_driver.h"

using namespace diagnostic_updater;

GpsDriver::GpsDriver() { state_period_ = ros::Duration(3); }

void GpsDriver::execLoop() {
  while (!terminating_) {
    std::unique_lock<std::mutex> lock(exec_mutex_);

    updateState();

    exec_cv_.wait_for(lock, std::chrono::milliseconds(50),
                      [&] { return terminating_.load(); });
  }
}
