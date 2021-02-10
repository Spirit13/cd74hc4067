#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/voltage_sampler/voltage_sampler.h"

namespace esphome {
namespace cd74hc4067 {

class CD74HC4067Sensor;

class CD74HC4067Component : public Component {
 public:
  ///void register_sensor(CD74HC4067Sensor *obj) { this->sensors_.push_back(obj); }
  /// Set up the internal sensor array.
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void set_s0_pin(GPIOPin *pin) { this->s0_pin_ = pin; }
  void set_s1_pin(GPIOPin *pin) { this->s1_pin_ = pin; }
  void set_s2_pin(GPIOPin *pin) { this->s2_pin_ = pin; }
  void set_s3_pin(GPIOPin *pin) { this->s3_pin_ = pin; }
  void set_adc_pin(uint8_t pin) { this->adc_pin_ = pin; }

 protected:
  float read_data_(uint8_t pin);
  GPIOPin *s0_pin_;
  GPIOPin *s1_pin_;
  GPIOPin *s2_pin_;
  GPIOPin *s3_pin_;
  uint8_t adc_pin_;    

  friend class CD74HC4067Sensor;
};

class CD74HC4067Sensor : public PollingComponent, public sensor::Sensor {
 public:
  CD74HC4067Sensor(CD74HC4067Component *parent, std::string name, uint8_t pin);
  
  void setup() override;
  void update() override;

 protected:
  CD74HC4067Component *parent_;
  uint8_t pin_;
};
}  // namespace cd74hc4067
}  // namespace esphome
