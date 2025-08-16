#include "qmi8658_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace qmi8658 {

static const char *TAG = "qmi8658";

void QMI8658Sensor::setup() {
  ESP_LOGI(TAG, "Initializing QMI8658 sensor");

  espp::Qmi8658::Config config;
  config.i2c_port = static_cast<i2c_port_t>(i2c_port_);
  config.sda_io_num = static_cast<gpio_num_t>(sda_pin_);
  config.scl_io_num = static_cast<gpio_num_t>(scl_pin_);
  config.address = address_;
  config.accel_range = accel_range_;
  config.accel_odr = accel_odr_;
  config.accel_lpf_mode = accel_lpf_mode_;
  config.gyro_range = gyro_range_;
  config.gyro_odr = gyro_odr_;
  config.gyro_lpf_mode = gyro_lpf_mode_;

  imu_ = std::make_unique<espp::Qmi8658>(config);
  imu_->init();

  if (interrupt_pin_ != GPIO_NUM_NC) {
    gpio_set_direction(interrupt_pin_, GPIO_MODE_INPUT);
    gpio_set_pull_mode(interrupt_pin_, GPIO_PULLUP_ONLY);
    ESP_LOGI(TAG, "Interrupt pin configured: GPIO%d", interrupt_pin_);
  }
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

// Range and ODR setters (string → enum mapping)
void QMI8658Sensor::set_accel_range(const std::string &range) {
  if (range == "2G") accel_range_ = espp::Qmi8658::AccelRange::RANGE_2G;
  else if (range == "4G") accel_range_ = espp::Qmi8658::AccelRange::RANGE_4G;
  else if (range == "8G") accel_range_ = espp::Qmi8658::AccelRange::RANGE_8G;
  else if (range == "16G") accel_range_ = espp::Qmi8658::AccelRange::RANGE_16G;
}

void QMI8658Sensor::set_accel_odr(const std::string &odr) {
  if (odr == "100HZ") accel_odr_ = espp::Qmi8658::ODR::ODR_100HZ;
  else if (odr == "200HZ") accel_odr_ = espp::Qmi8658::ODR::ODR_200HZ;
  else if (odr == "400HZ") accel_odr_ = espp::Qmi8658::ODR::ODR_400HZ;
}

void QMI8658Sensor::set_accel_lpf_mode(int mode) {
  accel_lpf_mode_ = mode;
}

void QMI8658Sensor::set_gyro_range(const std::string &range) {
  if (range == "64DPS") gyro_range_ = espp::Qmi8658::GyroRange::RANGE_64DPS;
  else if (range == "128DPS") gyro_range_ = espp::Qmi8658::GyroRange::RANGE_128DPS;
  else if (range == "256DPS") gyro_range_ = espp::Qmi8658::GyroRange::RANGE_256DPS;
  else if (range == "512DPS") gyro_range_ = espp::Qmi8658::GyroRange::RANGE_512DPS;
}

void QMI8658Sensor::set_gyro_odr(const std::string &odr) {
  if (odr == "100HZ") gyro_odr_ = espp::Qmi8658::ODR::ODR_100HZ;
  else if (odr == "200HZ") gyro_odr_ = espp::Qmi8658::ODR::ODR_200HZ;
  else if (odr == "400HZ") gyro_odr_ = espp::Qmi8658::ODR::ODR_400HZ;
}

void QMI8658Sensor::set_gyro_lpf_mode(int mode) {
  gyro_lpf_mode_ = mode;
}

}  // namespace qmi8658
}  // namespace esphome