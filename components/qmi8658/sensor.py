import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, CONF_NAME, CONF_UPDATE_INTERVAL

CONF_I2C_PORT = "i2c_port"
CONF_SDA_PIN = "sda_pin"
CONF_SCL_PIN = "scl_pin"
CONF_ADDRESS = "address"
CONF_INTERRUPT_PIN = "interrupt_pin"

CONF_ACCEL_RANGE = "acceleration_range"
CONF_ACCEL_ODR = "acceleration_odr"
CONF_ACCEL_LPF = "acceleration_lpf_mode"
CONF_GYRO_RANGE = "gyroscope_range"
CONF_GYRO_ODR = "gyroscope_odr"
CONF_GYRO_LPF = "gyroscope_lpf_mode"

qmi8658_ns = cg.esphome_ns.namespace("qmi8658")
QMI8658Sensor = qmi8658_ns.class_("QMI8658Sensor", cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(QMI8658Sensor),
    cv.Required(CONF_I2C_PORT): cv.int_,
    cv.Required(CONF_SDA_PIN): cv.int_,
    cv.Required(CONF_SCL_PIN): cv.int_,
    cv.Optional(CONF_ADDRESS, default=0x6B): cv.hex_int,
    cv.Optional(CONF_INTERRUPT_PIN): cv.int_,
    cv.Optional(CONF_UPDATE_INTERVAL, default="100ms"): cv.update_interval,

    cv.Optional(CONF_ACCEL_RANGE, default="4G"): cv.string_strict,
    cv.Optional(CONF_ACCEL_ODR, default="100HZ"): cv.string_strict,
    cv.Optional(CONF_ACCEL_LPF, default=0): cv.int_,
    cv.Optional(CONF_GYRO_RANGE, default="64DPS"): cv.string_strict,
    cv.Optional(CONF_GYRO_ODR, default="100HZ"): cv.string_strict,
    cv.Optional(CONF_GYRO_LPF, default=3): cv.int_,

    cv.Required("accel_x"): sensor.sensor_schema(),
    cv.Required("accel_y"): sensor.sensor_schema(),
    cv.Required("accel_z"): sensor.sensor_schema(),
    cv.Required("gyro_x"): sensor.sensor_schema(),
    cv.Required("gyro_y"): sensor.sensor_schema(),
    cv.Required("gyro_z"): sensor.sensor_schema(),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_i2c_port(config[CONF_I2C_PORT]))
    cg.add(var.set_sda_pin(config[CONF_SDA_PIN]))
    cg.add(var.set_scl_pin(config[CONF_SCL_PIN]))
    cg.add(var.set_address(config[CONF_ADDRESS]))

    if CONF_INTERRUPT_PIN in config:
        cg.add(var.set_interrupt_pin(config[CONF_INTERRUPT_PIN]))

    cg.add(var.set_accel_range(config[CONF_ACCEL_RANGE]))
    cg.add(var.set_accel_odr(config[CONF_ACCEL_ODR]))
    cg.add(var.set_accel_lpf_mode(config[CONF_ACCEL_LPF]))
    cg.add(var.set_gyro_range(config[CONF_GYRO_RANGE]))
    cg.add(var.set_gyro_odr(config[CONF_GYRO_ODR]))
    cg.add(var.set_gyro_lpf_mode(config[CONF_GYRO_LPF]))

    await sensor.register_sensor(var.accel_x_sensor, config["accel_x"])
    await sensor.register_sensor(var.accel_y_sensor, config["accel_y"])
    await sensor.register_sensor(var.accel_z_sensor, config["accel_z"])
    await sensor.register_sensor(var.gyro_x_sensor, config["gyro_x"])
    await sensor.register_sensor(var.gyro_y_sensor, config["gyro_y"])
    await sensor.register_sensor(var.gyro_z_sensor, config["gyro_z"])