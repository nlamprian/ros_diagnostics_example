#include <std_msgs/Empty.h>

#include "diagnostic_aggregator_example/analyzer/imu_analyzer.h"

PLUGINLIB_EXPORT_CLASS(diagnostic_aggregator::ImuAnalyzer,
                       diagnostic_aggregator::Analyzer)

namespace diagnostic_aggregator {

ImuAnalyzer::ImuAnalyzer() : matched_(false) {}

bool ImuAnalyzer::init(const std::string base_path, const ros::NodeHandle& n) {
  bool success = GenericAnalyzer::init(base_path, n);
  if (not success) return false;

  std::map<std::string, std::string> config;
  n.getParam("params", config);
  status_name_ = config["name"];
  status_message_ = config["message"];

  ros::NodeHandle nh = n;
  status_publisher_ = nh.advertise<std_msgs::Empty>("/imu_status", 1);

  return true;
}

std::vector<diagnostic_msgs::DiagnosticStatusPtr> ImuAnalyzer::report() {
  std::vector<diagnostic_msgs::DiagnosticStatusPtr> output =
      GenericAnalyzer::report();

  // Find requested status
  auto it = std::find_if(
      output.begin(), output.end(),
      [&](const diagnostic_msgs::DiagnosticStatusConstPtr& status) {
        return status->name.substr(status->name.find_last_of('/') + 1) ==
               status_name_;
      });

  if (it == output.end()) return output;

  bool matched = (*it)->message.find(status_message_) != std::string::npos;
  // Create event when message is matched
  if (not matched_ and matched) {
    std_msgs::Empty msg;
    status_publisher_.publish(msg);
  }
  matched_ = matched;

  return output;
}

}  // namespace diagnostic_aggregator
