// motor.h

#ifndef _MOTOR_h
#define _MOTOR_h
#include <stdint.h>

template<typename motor_unit = uint8_t>
class Motor {
	public:
		Motor(motor_unit start_val, motor_unit full_val, motor_unit half_val,
			motor_unit mtr_inc, motor_unit throt_pin, motor_unit rev_pin) : start_value(start_val),
			full_power_value(full_val), half_power_value(half_val), power_increment(mtr_inc),
			throttle_pin(throt_pin), reverse_pin(rev_pin) {};
		virtual ~Motor() {};
		virtual void power_toggle() = 0;
		motor_unit get_start_val() {
			return this->start_value;
		}
		motor_unit get_half_power_val() {
			return this->half_power_value;
		}
		motor_unit get_full_power_val() {
			return this->full_power_value;
		}
		motor_unit get_pwr_inc() {
			return this->power_increment;
		}
		motor_unit get_throttle_pin() {
			return this->throttle_pin;
		}
		motor_unit get_reverse_pin() {
			return this->reverse_pin;
		}

	private:
		motor_unit start_value;
		motor_unit half_power_value;
		motor_unit full_power_value;
		motor_unit power_increment;
		motor_unit throttle_pin;
		motor_unit reverse_pin;



};

#endif

