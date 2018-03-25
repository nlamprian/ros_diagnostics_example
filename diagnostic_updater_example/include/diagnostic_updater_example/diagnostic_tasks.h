#ifndef DIAGNOSTIC_TASKS_H
#define DIAGNOSTIC_TASKS_H

#include <mutex>

#include <diagnostic_updater/diagnostic_updater.h>
#include <ros/ros.h>

class StateTask : public diagnostic_updater::DiagnosticTask {
 public:
  StateTask(bool state) : DiagnosticTask("State"), state_(state) {}

  virtual void run(diagnostic_updater::DiagnosticStatusWrapper &stat) override {
    using namespace diagnostic_msgs;
    std::lock_guard<std::mutex> lock(mutex_);
    u_char level;
    std::string msg;
    if (state_) {
      level = DiagnosticStatus::OK;
      msg = "RUNNING";
    } else {
      level = DiagnosticStatus::ERROR;
      msg = "BROKEN";
    }
    stat.summary(level, msg);
  }

  void setState(bool state) {
    std::lock_guard<std::mutex> lock(mutex_);
    state_ = state;
  }

 private:
  std::mutex mutex_;
  bool state_;
};

#endif  // DIAGNOSTIC_TASKS_H
