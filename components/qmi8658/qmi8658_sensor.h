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

  // YAML-configurable setters
  void set_i2c_port(int port) { i2c_port_ = port; }
  void set_sda_pin(const std::string &pin);
  void set_scl_pin(const std::string &pin);
  void set_address(uint8_t addr) { address_ = addr; }
  void set_interrupt_pin(const std::string &pin);

  void set_accel_range(const std::string &range);
  void set_accel_odr(const std::string &odr);
  void set_accel_lpf_mode(int mode);

  void set_gyro_range(const std::string &range);
  void set_gyro_odr(const std::string &odr);
  void set_gyro_lpf_mode(int mode);

  // Sensor entities
  sensor::Sensor *accel_x_sensor;
  sensor::Sensor *accel_y_sensor;
  sensor::Sensor *accel_z_sensor;
  sensor::Sensor *gyro_x_sensor;
  sensor::Sensor *gyro_y_sensor;
  sensor::Sensor *gyro_z_sensor;

 protected:
  int i2c_port_;
  gpio_num_t sda_pin_;
  gpio_num_t scl_pin_;
  uint8_t address_;
  gpio_num_t interrupt_pin_ = GPIO_NUM_NC;

  int accel_lpf_mode_ = 0;
  int gyro_lpf_mode_ = 3;

  espp::Qmi8658::AccelRange accel_range_ = espp::Qmi8658::AccelRange::RANGE_4G;
  espp::Qmi8658::ODR accel_odr_ = espp::Qmi8658::ODR::ODR_100HZ;

  espp::Qmi8658::GyroRange gyro_range_ = espp::Qmi8658::GyroRange::RANGE_64DPS;
  espp::Qmi8658::ODR gyro_odr_ = espp::Qmi8658::ODR::ODR_100HZ;

  std::unique_ptr<espp::Qmi8658> imu_;
};

}  // namespace qmi8658
}  // namespace esphome