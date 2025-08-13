#include "qmi8658_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace qmi8658 {

static const char *TAG = "qmi8658";

void QMI8658Sensor::setup() {
  ESP_LOGI(TAG, "Setting up QMI8658");

  espp::Qmi8658::Config config;
  config.i2c_port = static_cast<i2c_port_t>(i2c_port_);
  config.sda_io_num = static_cast<gpio_num_t>(sda_pin_);
  config.scl_io_num = static_cast<gpio_num_t>(scl_pin_);
  config.address = address_;

  imu_ = std::make_unique<espp::Qmi8658>(config);
  imu_->init();
}

void QMI8658Sensor::update() {
  auto data = imu_->get_data();

  if (accel_x_sensor) accel_x_sensor->publish_state(data.accel[0]);
  if (accel_y_sensor) accel_y_sensor->publish_state(data.accel[1]);
  if (accel_z_sensor) accel_z_sensor->publish_state(data.accel[2]);

  if (gyro_x_sensor) gyro_x_sensor->publish_state(data.gyro[0]);
  if (gyro_y_sensor) gyro_y_sensor->publish_state(data.gyro[1]);
  if (gyro_z_sensor) gyro_z_sensor->publish_state(data.gyro[2]);
}

}  // namespace qmi8658
}  // namespace esphome