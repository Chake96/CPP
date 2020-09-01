// BLDC.h
#include "motor.h"

#ifndef _BLDC_H
#define _BLDC_H

template <typename motor_unit = uint8_t>
class BLDC final:public Motor<motor_unit> {

	private:
		static constexpr uint8_t default_half_power = 150U;
		motor_unit brake_pin;

	public:
		BLDC(motor_unit start_val, motor_unit full_val, motor_unit half_val, motor_unit mtr_inc,
			motor_unit throttle_pin, motor_unit reverse_pin, motor_unit brake_pin_in)
			:Motor<motor_unit>(start_val, full_val, half_val, mtr_inc, throttle_pin, reverse_pin),
			brake_pin(brake_pin_in), reversed(false) {}

		bool brake_pin_status = false;
		void power_toggle();
		void engage_motor(motor_unit power_level);
		void stop();
		void toggle_motor_brake();//toggles electricty on motor to brake 
		bool reversed = false;
		bool toggle_reverse();
		motor_unit current_power_level = 0;
};

template<typename motor_unit>
void BLDC<motor_unit>::power_toggle() {
	if (this->current_power_level > this->get_start_val()) {
		this->current_power_level = this->get_start_val();
	}
	else {
		this->current_power_level = this->get_full_power_val();
	}

	//write the new value to the motor controller
	analogWrite(this->current_power_level, this->current_power_level);
}


template<typename motor_unit>
void BLDC<motor_unit>::stop() {
	this->current_power_level = this->get_start_val();
	analogWrite(this->get_throttle_pin(), this->current_power_level);
}

template<typename motor_unit>
void BLDC<motor_unit>::toggle_motor_brake() {
	if (this->brake_pin_status) { //toggle braking on
		this->stop();
		digitalWrite(this->brake_pin, LOW);
		this->brake_pin_status = false;
	}else{ //toggle braking off
		digitalWrite(this->brake_pin, HIGH);
		this->brake_pin_status = true;
	}
}

template<typename motor_unit>
void BLDC<motor_unit>::engage_motor(motor_unit power_level = BLDC<motor_unit>::default_half_power) {
	analogWrite(this->get_throttle_pin(), power_level);
	this->current_power_level = power_level;
}

template<typename motor_unit>
bool BLDC<motor_unit>::toggle_reverse() {
	unsigned long start_time = 0, current_time = 0, wait_time =  100LU;
	this->stop();
	delay(1000);
	digitalWrite(this->get_reverse_pin(), LOW); //trigger BLDC controller to reverse
	current_time = millis(), start_time = millis();
	while(current_time - start_time < 1000LU){
		current_time = millis();
	}
	digitalWrite(this->get_reverse_pin(), HIGH);                                                                      
	this->reversed = !this->reversed;
	unsigned long current_time = millis(), start_time = millis(), WAIT_TIME = 1000UL;
	while(current_time - start_time < WAIT_TIME); //motors need 1 second to trigger reverse
	return this->reversed;
}

#endif
