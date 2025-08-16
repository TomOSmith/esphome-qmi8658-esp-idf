# ESPHome QMI8658 Component (ESP-IDF)

![ESPHome](https://img.shields.io/badge/ESPHome-External%20Component-blue)
![Sensor](https://img.shields.io/badge/sensor-QMI8658-blue)
![ESP-IDF](https://img.shields.io/badge/Framework-ESP--IDF-green)
![License](https://img.shields.io/badge/license-MIT-green)

**NOTE: This is work in progress and doesn't yet work.**

An ESPHome external component for the [QMI8658](https://www.qstcorp.com/product/6-axis/qmi8658.html) 6-axis IMU sensor (accelerometer + gyroscope), built on the native ESP-IDF framework using the official [`espp/qmi8658`](https://components.espressif.com/components/espp/qmi8658) driver.

---

## ✨ Features

- ✅ ESP-IDF native integration
- ✅ Configurable I²C pins, address, and port
- ✅ Optional interrupt pin
- ✅ YAML-configurable acceleration and gyroscope ranges, ODRs, and LPF modes
- ✅ Sensor entities for all 6 axes

---

## 📦 Installation

Clone this repo into your ESPHome config folder:

```bash
git clone https://github.com/TomOSmith/esphome-qmi8658-esp-idf.git
```

Reference the component in your ESPHome YAML:

```yaml
external_components:
  - source: github://TomOSmith/esphome-qmi8658-esp-idf/external_components/qmi8658_esphome
```

---

## 🧪 Example Configuration

```yaml
esphome:
  name: qmi8658_test
  platform: ESP32
  board: esp32-s3-devkitc-1
  build_platform: esp-idf

external_components:
  - source: github://TomOSmith/esphome-qmi8658-esp-idf/external_components/qmi8658_esphome

sensor:
  - platform: qmi8658
    i2c_port: 0
    sda_pin: GPIO15
    scl_pin: GPIO14
    address: 0x6B
    interrupt_pin: GPIO21
    acceleration_range: 2G
    acceleration_odr: 100HZ
    acceleration_lpf_mode: 0
    gyroscope_range: 64DPS
    gyroscope_odr: 100HZ
    gyroscope_lpf_mode: 3
    update_interval: 100ms

    accel_x:
      name: "Accel X"
    accel_y:
      name: "Accel Y"
    accel_z:
      name: "Accel Z"
    gyro_x:
      name: "Gyro X"
    gyro_y:
      name: "Gyro Y"
    gyro_z:
      name: "Gyro Z"
```

---

## 🧰 Supported Configuration Options

| Option                 | Description                            | Example       |
|------------------------|----------------------------------------|---------------|
| `i2c_port`             | I²C bus number                         | `0`           |
| `sda_pin`, `scl_pin`   | GPIOs for I²C                          | `GPIO21`      |
| `address`              | I²C address of QMI8658                 | `0x6B`        |
| `interrupt_pin`        | Optional GPIO for INT output           | `GPIO13`      |
| `acceleration_range`   | ±2G, ±4G, ±8G, ±16G                    | `4G`          |
| `acceleration_odr`     | Output data rate (Hz)                  | `100HZ`       |
| `acceleration_lpf_mode`| Low-pass filter mode (0–3)             | `0`           |
| `gyroscope_range`      | ±16DPS to ±2048DPS                     | `64DPS`       |
| `gyroscope_odr`        | Output data rate (Hz)                  | `100HZ`       |
| `gyroscope_lpf_mode`   | Low-pass filter mode (0–3)             | `3`           |
| `update_interval`      | Polling interval                       | `100ms`       |

---

## 🧠 Notes

- Requires ESPHome with `build_platform: esp-idf`
- Compatible with ESP32, ESP32-S3, and other ESP-IDF-supported boards
- Uses the official [espp/qmi8658](https://components.espressif.com/components/espp/qmi8658) driver

---

## 📜 License

MIT © [TomOSmith](https://github.com/TomOSmith)