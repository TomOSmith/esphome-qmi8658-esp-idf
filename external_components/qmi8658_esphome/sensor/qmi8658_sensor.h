#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "qmi8658.hpp"

namespace esphome {
namespace qmi8658 {

class QMI8658Sensor : public PollingComponent {
 public:
  void setup() override;
  void update() override;

  void set_i2c_port(int port) { i2c_port_ = port; }
  void set_sda_pin(int pin) { sda_pin_ = pin; }
  void set_scl_pin(int pin) { scl_pin_ = pin; }
  void set_address(uint8_t addr) { address_ = addr; }

  sensor::Sensor *accel_x_sensor;
  sensor::Sensor *accel_y_sensor;
  sensor::Sensor *accel_z_sensor;
  sensor::Sensor *gyro_x_sensor;
  sensor::Sensor *gyro_y_sensor;
  sensor::Sensor *gyro_z_sensor;

 protected:
  int i2c_port_;
  int sda_pin_;
  int scl_pin_;
  uint8_t address_;
  std::unique_ptr<espp::Qmi8658> imu_;
};

}  // namespace qmi8658
}  // namespace esphome