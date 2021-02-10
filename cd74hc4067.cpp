#include "esphome/core/log.h"
#include "cd74hc4067.h"
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

namespace esphome {
namespace cd74hc4067 {

static const char *TAG = "cd74hc4067";

float CD74HC4067Component::get_setup_priority() const { return setup_priority::HARDWARE; }

void CD74HC4067Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up CD74HC4067...");
  this->s0_pin_->pin_mode(OUTPUT);
  this->s1_pin_->pin_mode(OUTPUT);
  this->s2_pin_->pin_mode(OUTPUT);
  this->s3_pin_->pin_mode(OUTPUT);
  GPIOPin(this->adc_pin_, INPUT).setup();
}
void CD74HC4067Component::dump_config() {
  ESP_LOGCONFIG(TAG, "Setting up CD74HC4067...");
}

float CD74HC4067Component::read_data_(uint8_t pin) {
   this->s0_pin_->digital_write(bitRead(pin, 0));
   this->s1_pin_->digital_write(bitRead(pin, 1));
   this->s2_pin_->digital_write(bitRead(pin, 2));
   this->s3_pin_->digital_write(bitRead(pin, 3));
   delay(10);
   analogRead(this->adc_pin_);
   float muxvalue = analogRead(this->adc_pin_);
   return muxvalue / 1024.0f;
}

CD74HC4067Sensor::CD74HC4067Sensor(CD74HC4067Component *parent, std::string name, uint8_t pin)
    : PollingComponent(1000), parent_(parent), pin_(pin) {
  this->set_name(name);
}
void CD74HC4067Sensor::setup() { LOG_SENSOR("", "Setting up CD74HC4067 Sensor '%s'...", this); }
void CD74HC4067Sensor::update() {
  float value_v = this->parent_->read_data_(pin_);
  this->publish_state(value_v);
}

}  // namespace cd74hc4067
}  // namespace esphome
