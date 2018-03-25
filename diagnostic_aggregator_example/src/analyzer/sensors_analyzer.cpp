#include <std_msgs/Int8.h>

#include "diagnostic_aggregator_example/analyzer/sensors_analyzer.h"

PLUGINLIB_EXPORT_CLASS(diagnostic_aggregator::SensorsAnalyzer,
                       diagnostic_aggregator::Analyzer)

namespace diagnostic_aggregator {

SensorsAnalyzer::SensorsAnalyzer()
    : level_(diagnostic_msgs::DiagnosticStatus::OK) {}

bool SensorsAnalyzer::init(const std::string base_path,
                           const ros::NodeHandle& n) {
  bool success = AnalyzerGroup::init(base_path, n);
  if (not success) return false;

  ros::NodeHandle nh = n;
  status_publisher_ = nh.advertise<std_msgs::Int8>("/sensors_status", 1);

  return true;
}

std::vector<diagnostic_msgs::DiagnosticStatusPtr> SensorsAnalyzer::report() {
  std::vector<diagnostic_msgs::DiagnosticStatusPtr> output =
      AnalyzerGroup::report();

  // Find group status
  auto it = std::find_if(
      output.begin(), output.end(),
      [&](const diagnostic_msgs::DiagnosticStatusConstPtr& status) {
        return status->name == getPath();
      });

  int8_t level = (*it)->level;
  // Create event on a transition from OK to OTHER
  if (level != level_ and level_ == diagnostic_msgs::DiagnosticStatus::OK) {
    std_msgs::Int8 msg;
    msg.data = level;
    status_publisher_.publish(msg);
  }
  level_ = level;

  return output;
}

}  // namespace diagnostic_aggregator
