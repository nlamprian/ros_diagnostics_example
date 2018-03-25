#ifndef GPS_DRIVER_H
#define GPS_DRIVER_H

#include "diagnostic_updater_example/driver_base.h"

class GpsDriver : public DriverBase {
 public:
  GpsDriver();

 private:
  virtual void execLoop() override;
};

#endif  // GPS_DRIVER_H
