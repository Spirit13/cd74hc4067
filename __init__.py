import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.const import CONF_ATTENUATION, CONF_ID, CONF_PIN, ICON_FLASH, UNIT_VOLT

AUTO_LOAD = ['sensor', 'voltage_sampler']
MULTI_CONF = True

cd74hc4067_ns = cg.esphome_ns.namespace('cd74hc4067')
CD74HC4067Component = cd74hc4067_ns.class_('CD74HC4067Component', cg.Component)
CONF_S0='s0_pin'
CONF_S1='s1_pin'
CONF_S2='s2_pin'
CONF_S3='s3_pin'
CONF_ADC='adc_pin'


def validate_adc_pin(value):
    vcc = str(value).upper()
    if vcc == 'VCC':
        return cv.only_on_esp8266(vcc)
    return pins.analog_pin(value)

CONFIG_SCHEMA = cv.Schema({
	cv.GenerateID(): cv.declare_id(CD74HC4067Component),
    cv.Required(CONF_S0): pins.gpio_output_pin_schema,
    cv.Required(CONF_S1): pins.gpio_output_pin_schema,
    cv.Required(CONF_S2): pins.gpio_output_pin_schema,
    cv.Required(CONF_S3): pins.gpio_output_pin_schema,  
    cv.Required(CONF_ADC): pins.analog_pin,
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)	
    s0_pin = yield cg.gpio_pin_expression(config[CONF_S0])
    cg.add(var.set_s0_pin(s0_pin))
    s1_pin = yield cg.gpio_pin_expression(config[CONF_S1])
    cg.add(var.set_s1_pin(s1_pin))
    s2_pin = yield cg.gpio_pin_expression(config[CONF_S2])
    cg.add(var.set_s2_pin(s2_pin))
    s3_pin = yield cg.gpio_pin_expression(config[CONF_S3])
    cg.add(var.set_s3_pin(s3_pin))
    #adc_pin = yield cg.gpio_pin_expression(config[CONF_ADC])
    cg.add(var.set_adc_pin(config[CONF_ADC]))

