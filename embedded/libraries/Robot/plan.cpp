// 
// 
// 

#include "plan.h"
#include <HardwareSerial.h>

plan::plan() {
	this->commands = nullptr;
	this->length = 0;
	this->last_command = this->commands;
}



void plan::append(command& new_command) {
	if (this->commands == nullptr) {
		this->commands = new command[1];
		this->commands[0] = new_command;
		this->length = 1;
	}
	else {
		command temp[this->length];
		memcpy(temp, this->commands, sizeof(command)*this->length);
		delete [] this->commands;
		this->commands = new command[this->length+1];
		memcpy(this->commands, temp, sizeof(command)*this->length);
		this->commands[this->length] = new_command;
		this->length += 1;
	}
}

const uint16_t plan::get_length() {
	return this->length;
}

command plan::pop() {
	command return_plan;
	if (this->length == 1) {
		this->length = 0;
		return_plan = this->commands[0];
		this->commands = nullptr;
		this->last_command = this->commands;
	}
	else {
		return_plan = this->commands[this->length-1];
		command buff[this->length];
		memcpy(&buff, &this->commands[0], sizeof(buff));
		this->length -= 1;

		delete [] this->commands;
		this->commands = new command[this->length];
		memcpy(&this->commands[0], &buff, sizeof(command)*this->length);
	}
	return return_plan;
}

const command& plan::top() {
	return this->commands[0];
}

const command& plan::get_command(uint16_t command_index) {
	command cmd_ref;
	cmd_ref.duration = this->commands[command_index].duration;
	cmd_ref.type = this->commands[command_index].type;
	return this->commands[command_index];
}

void plan::print() {
	Serial.print("Plan has ");
	Serial.print(this->get_length(), DEC);
	Serial.println(" Command(s):");
	for (uint16_t i = 0; i < this->get_length(); i++) {
		const command copy = command(this->get_command(i));
		Serial.print("Command #");
		Serial.print(i, DEC);
		Serial.println(":");
		Serial.print("Type: ");
		Serial.println(copy.type);
		Serial.print("Duration (feet): ");
		Serial.println(copy.duration, 4);
		Serial.println("---------------------");
	}
	Serial.println(' ');
}