#ifndef IMU_ANALYZER_H
#define IMU_ANALYZER_H

#include <diagnostic_aggregator/generic_analyzer.h>

namespace diagnostic_aggregator {

class ImuAnalyzer : public GenericAnalyzer {
 public:
  ImuAnalyzer();
  virtual bool init(const std::string base_path, const ros::NodeHandle &n);
  virtual std::vector<diagnostic_msgs::DiagnosticStatusPtr> report();

 private:
  std::string status_name_, status_message_;
  ros::Publisher status_publisher_;
  bool matched_;
};

}  // namespace diagnostic_aggregator

#endif  // IMU_ANALYZER_H
