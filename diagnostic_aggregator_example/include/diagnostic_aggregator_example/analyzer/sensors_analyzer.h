#ifndef SENSORS_ANALYZER_H
#define SENSORS_ANALYZER_H

#include <diagnostic_aggregator/analyzer_group.h>

namespace diagnostic_aggregator {

class SensorsAnalyzer : public AnalyzerGroup {
 public:
  SensorsAnalyzer();
  virtual bool init(const std::string base_path, const ros::NodeHandle &n);
  virtual std::vector<diagnostic_msgs::DiagnosticStatusPtr> report();

 private:
  ros::Publisher status_publisher_;
  int8_t level_;
};

}  // namespace diagnostic_aggregator

#endif  // SENSORS_ANALYZER_H
