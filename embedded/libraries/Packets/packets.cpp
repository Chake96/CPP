#include <packets.h>
#include <string.h>
#include <plan.h>

//type conversion functions


uint32_t htonf(float f)
{
	uint32_t p;
	uint32_t sign;

	if (f < 0) { sign = 1; f = -f; }
	else { sign = 0; }

	p = ((((uint32_t)f) & 0x7fff) << 16) | (sign << 31); // whole part and sign
	p |= (uint32_t)(((f - (int)f) * 65536.0f)) & 0xffff; // fraction

	return p;
}

float ntohf(uint32_t p)
{
	float f = ((p >> 16) & 0x7fff); // whole part
	f += (p & 0xffff) / 65536.0f; // fraction

	if (((p >> 31) & 0x1) == 0x1) { f = -f; } // sign bit set

	return f;
}


//Number PACKET
packets::number_packet::number_packet() {
	this->data = new uint8_t(0);
	this->type = static_cast<uint8_t>(packets::packet_types::NUMBER);
}


packets::number_packet::number_packet(uint16_t send_addr, uint16_t dest_addr, uint8_t gateway_addr,
	uint_fast16_t p_id, uint8_t* p_data) {
	this->type = static_cast<uint8_t>(packets::packet_types::NUMBER);
	this->sender_address = send_addr;
	this->destination_address = dest_addr;
	this->network_gateway_address = gateway_addr;
	this->id = p_id;
	this->data = p_data;
	this->size = packet::minimum_packet_size + (sizeof(this->data)/sizeof(this->data[0]) + 1);
}


inline void packets::number_packet::set_data(uint8_t* data_in) {
	this->data = data_in;
}

const uint8_t* packets::number_packet::get_data() {
	return this->data;
}

uint8_t* packets::number_packet::serialize() {
	uint8_t* result_buf = new uint8_t[this->size];
	uint8_t type = static_cast<uint8_t>(this->type);
	uint8_t id_msb = static_cast<uint8_t>(id >> 8 & 0x00FF);
	uint8_t id_lsb = static_cast<uint8_t>(id);
	uint8_t size = static_cast<uint8_t>(this->size);
	uint8_t send_addr_msb = static_cast<uint8_t>(sender_address >> 8 & 0x00FF);
	uint8_t send_addr_lsb = static_cast<uint8_t>(sender_address);
	uint8_t dest_addr_msb = static_cast<uint8_t>(destination_address >> 8 & 0x00FF);
	uint8_t dest_addr_lsb = static_cast<uint8_t>(destination_address);
	uint8_t gate_way_addr = this->network_gateway_address;

	result_buf[0] = type;
	result_buf[1] = size;
	result_buf[2] = id_msb;
	result_buf[3] = id_lsb;
	result_buf[4] = send_addr_msb;
	result_buf[5] = send_addr_lsb;
	result_buf[6] = dest_addr_msb;
	result_buf[7] = dest_addr_lsb;
	result_buf[8] = gate_way_addr;
	//serialize the data
	for (uint8_t i = 0; i < this->size - packet::minimum_packet_size; i++) {
		result_buf[packet::minimum_packet_size + 1 + i] = this->data[i];
	}
	return result_buf;
}

void packets::number_packet::deserialize(uint8_t* s_pckt) {
	//deserialize data
	packet::deserialize(s_pckt);
	uint8_t i = 0;
	this->data = new uint8_t[s_pckt[1]];
	for (uint8_t byte = packet::minimum_packet_size + 1; byte <= s_pckt[1]; byte++) {
		this->data[i] = s_pckt[byte];
		i += 1;
	}
}

void packets::number_packet::print() {
	Serial.println("----------Number PACKET----------");
	packet::print();
	uint32_t size = this->size - packet::minimum_packet_size -1;
	
	Serial.print("Data Size: ");
	Serial.println(this->size - packet::minimum_packet_size -1);
	Serial.print("Data: ");
	if(size == 2){
		#ifdef DEBUG
			Serial.println("UINT16_T # sent");
		#endif
		uint16_t data = (uint16_t) this->data[1] | this->data[0] << 8;
		Serial.println(data);
	}else{
		for(size_t i = 0 ; i< size; i++)
			Serial.print(this->data[i]);
		Serial.println();
	}
	Serial.println("--------Number Packet End--------");
}



//Plan Packet
packets::plan_packet::plan_packet() {
	this->_plan = plan();
	this->type = static_cast<uint8_t>(packets::packet_types::PLAN);
}

packets::plan_packet::plan_packet(uint16_t send_addr, uint16_t dest_addr, uint8_t gateway_addr,
	uint_fast16_t p_id, const plan& plan_in) {
	this->type = static_cast<uint8_t>(packets::packet_types::PLAN);
	this->sender_address = send_addr;
	this->destination_address = dest_addr;
	this->network_gateway_address = gateway_addr;
	this->id = p_id;
	this->_plan = plan_in;
	this->size = packet::minimum_packet_size + (plan_in.get_length()*sizeof(command));
	if (this->size > packet::max_size()) {
		Serial.println("WARNING: PLAN NEEDS TO BE SPLIT BETWEEN MULTIPLE PACKETS");
	}
}

void packets::plan_packet::set_plan(const plan& plan_in) {
	this->_plan = plan_in;
}

plan packets::plan_packet::get_plan() {
	return this->_plan;
}

uint8_t* packets::plan_packet::serialize() {
	uint8_t* result_buf = new uint8_t[this->size];
	uint8_t type = static_cast<uint8_t>(this->type);
	uint8_t id_msb = static_cast<uint8_t>(id >> 8 & 0x00FF);
	uint8_t id_lsb = static_cast<uint8_t>(id);
	uint8_t size = static_cast<uint8_t>(this->size);
	uint8_t send_addr_msb = static_cast<uint8_t>(sender_address >> 8 & 0x00FF);
	uint8_t send_addr_lsb = static_cast<uint8_t>(sender_address);
	uint8_t dest_addr_msb = static_cast<uint8_t>(destination_address >> 8 & 0x00FF);
	uint8_t dest_addr_lsb = static_cast<uint8_t>(destination_address);
	uint8_t gate_way_addr = this->network_gateway_address;

	result_buf[0] = type;
	result_buf[1] = size;
	result_buf[2] = id_msb;
	result_buf[3] = id_lsb;
	result_buf[4] = send_addr_msb;
	result_buf[5] = send_addr_lsb;
	result_buf[6] = dest_addr_msb;
	result_buf[7] = dest_addr_lsb;
	result_buf[8] = gate_way_addr;

	//serialize wasnt working properly?
	//result_buf = this->packet::serialize();
	uint32_t conv_duration = 0;
	
	uint16_t num_commands = this->_plan.get_length();
	uint8_t buffer_indx = 0;
	plan current_plan = this->_plan;
	for (uint16_t cmd_i = 0; cmd_i < num_commands; cmd_i++) {
		command curr_command = current_plan.get_command(cmd_i);
		conv_duration = 0;
		conv_duration = htonf(curr_command.duration);
		result_buf[packet::minimum_packet_size + buffer_indx + 1] = curr_command.type;
		result_buf[packet::minimum_packet_size + buffer_indx + 2] = conv_duration >> 24 & 0x00FF;
		result_buf[packet::minimum_packet_size + buffer_indx + 3] = conv_duration >> 16 & 0x00FF;
		result_buf[packet::minimum_packet_size + buffer_indx + 4] = conv_duration >> 8 & 0x00FF;
		result_buf[packet::minimum_packet_size + buffer_indx + 5] = conv_duration;
	
		buffer_indx += sizeof(command);
	}

	return result_buf;
}

void packets::plan_packet::deserialize(uint8_t* s_pckt) {
	//deserialize data
	this->packet::deserialize(s_pckt);
	
	uint32_t conv_duration = 0;
	uint16_t indx = packet::minimum_packet_size + 1;
	command curr_cmd;
	for (indx; indx <= this->size; indx += sizeof(command)) {
		uint8_t type = s_pckt[indx];
		conv_duration = s_pckt[indx + 4]|
			(uint32_t)s_pckt[indx + 3] << 8 |
			(uint32_t)s_pckt[indx + 2] << 16 |
			(uint32_t)s_pckt[indx + 1] << 24;
		curr_cmd.duration = ntohf(conv_duration);
		curr_cmd.type = s_pckt[indx];
		conv_duration = 0;
		this->get_plan().append(curr_cmd);
	}
}

void packets::plan_packet::print() {
	Serial.println("----------Plan PACKET----------");
	packet::print();
	Serial.println("Plan: ");
	this->_plan.print();
	Serial.println("--------Plan Packet End--------");
}




//ERROR Packet
packets::error_packet::error_packet(){
	this->data = new char("\0");
	this->type = static_cast<uint8_t>(packets::packet_types::ERROR);
}

packets::error_packet::error_packet(uint16_t send_addr, uint16_t dest_addr, uint8_t gateway_addr,
	uint_fast16_t p_id, char* p_data) {
	this->type = static_cast<uint8_t>(packets::packet_types::ERROR);
	this->sender_address = send_addr;
	this->destination_address = dest_addr;
	this->network_gateway_address = gateway_addr;
	this->id = p_id;
	this->data = p_data;
	this->size = packet::minimum_packet_size + (strlen(this->data)+1);
}


inline void packets::error_packet::set_data(char* data_in) {
	strncpy(this->data, data_in, strlen(data_in)+1);
}

inline const char* packets::error_packet::get_data() {
	return this->data;
}

uint8_t* packets::error_packet::serialize() {
	uint8_t* result_buf = packet::serialize();
	//serialize the data
	for (uint8_t i = 0; i < strlen(this->data) + 1; i++) {
		result_buf[packet::minimum_packet_size + 1 + i] = this->data[i];
	}
	return result_buf;
}

void packets::error_packet::deserialize(uint8_t* s_pckt) {
	//deserialize data
	packet::deserialize(s_pckt);
	uint8_t i = 0;
	this->data = new char[s_pckt[1]];
	for (uint8_t byte = packet::minimum_packet_size + 1; byte <= s_pckt[1]; byte++) {
		this->data[i] = s_pckt[byte];
		i += 1;
	}
}

void packets::error_packet::print() {
	Serial.println("----------ERROR PACKET----------");
	packet::print();
	Serial.print("Data Size: ");
	Serial.println(strlen(this->data));
	Serial.print("Data: ");
	Serial.println(this->data);
	Serial.println("--------Error Packet End--------");
}

//COMMUNICATION PACKET
packets::comm_packet::comm_packet() {
	strncpy(this->data, "\0", sizeof("\0"));
	this->type = static_cast<uint8_t>(packets::packet_types::COMMUNICATION);
}


packets::comm_packet::comm_packet(uint16_t send_addr, uint16_t dest_addr, uint8_t gateway_addr,
	uint_fast16_t p_id, char* p_data) {
	this->type = static_cast<uint8_t>(packets::packet_types::COMMUNICATION);
	this->sender_address = send_addr;
	this->destination_address = dest_addr;
	this->network_gateway_address = gateway_addr;
	this->id = p_id;
	this->data = p_data;
	this->size = packet::minimum_packet_size + (strlen(this->data) +1);
}


void packets::comm_packet::set_data(char* data_in) {
	// delete this->data;
	strncpy(this->data, data_in, strlen(data_in));
}

const char* packets::comm_packet::get_data() {
	return this->data;
}

uint8_t* packets::comm_packet::serialize() {
	uint8_t* result_buf = new uint8_t[this->size];
	uint8_t id_msb = static_cast<uint8_t>(id >> 8 & 0x00FF);
	uint8_t id_lsb = static_cast<uint8_t>(id);
	uint8_t size = static_cast<uint8_t>(this->size);
	uint8_t send_addr_msb = static_cast<uint8_t>(sender_address >> 8 & 0x00FF);
	uint8_t send_addr_lsb = static_cast<uint8_t>(sender_address);
	uint8_t dest_addr_msb = static_cast<uint8_t>(destination_address >> 8 & 0x00FF);
	uint8_t dest_addr_lsb = static_cast<uint8_t>(destination_address);
	uint8_t gate_way_addr = this->network_gateway_address;

	result_buf[0] = this->type;
	result_buf[1] = size;
	result_buf[2] = id_msb;
	result_buf[3] = id_lsb;
	result_buf[4] = send_addr_msb;
	result_buf[5] = send_addr_lsb;
	result_buf[6] = dest_addr_msb;
	result_buf[7] = dest_addr_lsb;
	result_buf[8] = gate_way_addr;
	//serialize the data
	for(uint8_t i = 0; i < strlen(this->data)+1; i++){
		result_buf[packet::minimum_packet_size+1 + i] = this->data[i];
	}
	return result_buf;
}

void packets::comm_packet::deserialize(uint8_t* s_pckt) {
	//deserialize data
	this->packet::deserialize(s_pckt);
	uint8_t i = 0;
	this->data = new char[s_pckt[1]];
	for (uint8_t byte = packet::minimum_packet_size+1; byte <= s_pckt[1]; byte++) {
		this->data[i] = s_pckt[byte];
		i += 1;
	}
}

void packets::comm_packet::print() {
	Serial.println("----------COMMUNICATION PACKET----------");
	packet::print();
	Serial.print("Data Size: ");
	Serial.println(strlen(this->data));
	Serial.print("Data: ");
	Serial.println(this->data);
	Serial.println("--------COMMUNICATION Packet End--------");
}

//PACKETS RELATED TO SENSORS
//ULTRASONIC
packets::ultrasonic_packet::ultrasonic_packet() {
	this->type = packets::packet_types::ULTRASONIC;
}

packets::ultrasonic_packet::ultrasonic_packet(uint16_t send_addr, uint16_t dest_addr, uint8_t gateway_addr,
	uint16_t p_id, uint8_t s_id, uint16_t dist) {
	this->sender_address = send_addr;
	this->destination_address = dest_addr;
	this->network_gateway_address = gateway_addr;
	this->id = p_id;
	this->sensor_id = s_id;
	this->distance = dist;
	this->type = packets::packet_types::ULTRASONIC;
	this->size = sizeof(*this);
}


inline void packets::ultrasonic_packet::set_data(const uint8_t s_id, const uint16_t data_in) {
	this->sensor_id = s_id;
	this->distance = data_in; 
}

inline void packets::ultrasonic_packet::set_sensor_id(const uint8_t s_id) {
	this->sensor_id = s_id;
}

inline void packets::ultrasonic_packet::set_distance(const uint16_t distance_in) {
	this->distance = distance_in;
}

inline const pair<uint8_t, uint16_t> packets::ultrasonic_packet::get_data() {
	return pair<uint8_t, uint16_t>(this->sensor_id, this->distance);
}

inline const uint8_t packets::ultrasonic_packet::get_sensor_id() {
	return this->sensor_id;
}

inline const uint16_t packets::ultrasonic_packet::get_distance() {
	return this->distance;
}

uint8_t* packets::ultrasonic_packet::serialize() {
	uint8_t* result_buffer = packet::serialize();
	uint8_t id = this->sensor_id;
	uint8_t dist_msb = (this->distance >> 8) & 0x00FF;
	uint8_t dist_lsb = this->distance;

	result_buffer[packet::minimum_packet_size + 1] = id;
	result_buffer[packet::minimum_packet_size + 2] = dist_msb;
	result_buffer[packet::minimum_packet_size + 3] = dist_lsb;
	return result_buffer;
}

void packets::ultrasonic_packet::deserialize(uint8_t* s_packet) {
	packet::deserialize(s_packet);
	this->sensor_id = s_packet[packet::minimum_packet_size + 1];
	this->distance = (s_packet[packet::minimum_packet_size + 2] << 8) | s_packet[packet::minimum_packet_size + 3];
}

void packets::ultrasonic_packet::print() {
	Serial.println("-------------ULTRASONIC Packet-------------");
	packet::print();
	Serial.println("Data: ");
	Serial.print("Sensor ID: ");
	Serial.println(this->sensor_id, DEC);
	Serial.print("Distance: ");
	Serial.println(this->distance, DEC);
	Serial.println("-----------ULTRASONIC Packet END-----------");

}

//GYRO & Accelerometer
packets::accel_gyro_packet::accel_gyro_packet() {
	this->type = packets::ACCEL_GYRO;
}

packets::accel_gyro_packet::accel_gyro_packet(uint16_t send_addr, uint16_t dest_addr, uint8_t gate_addr,
	uint16_t pckt_id, float* eulers_in, float* ypr_in) {
	this->sender_address = send_addr;
	this->destination_address = dest_addr;
	this->network_gateway_address = gate_addr;
	this->type = packets::ACCEL_GYRO;
	this->id = pckt_id;
	for (size_t i = 0; i < this->array_size; i++) {
		this->euler[i] = eulers_in[i];
		this->yaw_pitch_roll[i] = ypr_in[i];
	}
	this->size = sizeof(*this);
}

void packets::accel_gyro_packet::set_euler(const float e_arr[]) {
	for(size_t i = 0; i < this->array_size; i++){
		this->euler[i] = e_arr[i];
	}
}


void packets::accel_gyro_packet::set_yaw_ptch_roll(float ypr[]) {
	for (size_t i = 0; i < this->array_size; i++){
		this->yaw_pitch_roll[i] = ypr[i];
	}
}

uint8_t* packets::accel_gyro_packet::serialize() {
	static_assert(sizeof(float) == 4, "FLOAT SIZE ERROR: Not Equal to 4 Bytes, CANNOT SERIALIZE");
	uint8_t* return_buffer = packet::serialize();
	uint32_t eulers32[this->array_size] = { htonf(this->euler[0]), htonf(this->euler[1]), htonf(this->euler[2]) };
	uint32_t ypr32[this->array_size] = { htonf(this->yaw_pitch_roll[0]), htonf(this->yaw_pitch_roll[1]), htonf(this->yaw_pitch_roll[2]) };
	uint8_t conv8_float[4];
	

	//convert eulers to bytes and add to the tail buffer
	uint8_t buffer_start_pos = 0;
	for (uint8_t euler_it = 0; euler_it < this->array_size; euler_it++) {
		conv8_float[0] = (eulers32[euler_it] >> 24) & 0x00FF;
		conv8_float[1] = (eulers32[euler_it] >> 16) & 0x00FF;
		conv8_float[2] = (eulers32[euler_it] >> 8) & 0x00FF;
		conv8_float[3] = eulers32[euler_it];
		return_buffer[packet::minimum_packet_size + 1 + buffer_start_pos] = conv8_float[0];
		return_buffer[packet::minimum_packet_size + 2 + buffer_start_pos] = conv8_float[1];
		return_buffer[packet::minimum_packet_size + 3 + buffer_start_pos] = conv8_float[2];
		return_buffer[packet::minimum_packet_size + 4 + buffer_start_pos] = conv8_float[3];
		buffer_start_pos += 4;
	}

	//convert yaw,pitch,rolls and add to the tail of the buffer
	for (uint8_t ypr_it = 0; ypr_it < this->array_size; ypr_it++) {
		conv8_float[0] = (ypr32[ypr_it] >> 24) & 0x00FF;
		conv8_float[1] = (ypr32[ypr_it] >> 16) & 0x00FF;
		conv8_float[2] = (ypr32[ypr_it] >> 8) & 0x00FF;
		conv8_float[3] = ypr32[ypr_it];
		return_buffer[packet::minimum_packet_size + 1 + buffer_start_pos] = conv8_float[0];
		return_buffer[packet::minimum_packet_size + 2 + buffer_start_pos] = conv8_float[1];
		return_buffer[packet::minimum_packet_size + 3 + buffer_start_pos] = conv8_float[2];
		return_buffer[packet::minimum_packet_size + 4 + buffer_start_pos] = conv8_float[3];
		buffer_start_pos += 4;
	}
	return return_buffer;
}

void packets::accel_gyro_packet::deserialize(uint8_t* packet) {
	packet::deserialize(packet);
	//uint8_t conv8_float[4];

	//convert eulers from bytes to floats 
	uint8_t buffer_start_pos = 0;
	uint32_t cov_bytes = 0;
	for(uint8_t euler_it = 0; euler_it < this->array_size; euler_it++) {
		cov_bytes = packet[packet::minimum_packet_size + 4 + buffer_start_pos] |
			(uint32_t)packet[packet::minimum_packet_size + 3 + buffer_start_pos] << 8 |
			(uint32_t)packet[packet::minimum_packet_size + 2 + buffer_start_pos] << 16 |
			(uint32_t)packet[packet::minimum_packet_size + 1 + buffer_start_pos] << 24;
		this->euler[euler_it] = ntohf(cov_bytes);
		buffer_start_pos += 4;
	}

	//convert yaw,pitch,roll from bytes to floats
	for (uint8_t ypr_it = 0; ypr_it < this->array_size; ypr_it++) {
		cov_bytes = packet[packet::minimum_packet_size + 4 + buffer_start_pos] |
			(uint32_t)packet[packet::minimum_packet_size + 3 + buffer_start_pos] << 8 |
			(uint32_t)packet[packet::minimum_packet_size + 2 + buffer_start_pos] << 16 |
			(uint32_t)packet[packet::minimum_packet_size + 1 + buffer_start_pos] << 24;
		this->yaw_pitch_roll[ypr_it] = ntohf(cov_bytes);
		buffer_start_pos += 4;
	}
	
}



void packets::accel_gyro_packet::print() {
	Serial.println("-------------Acceleration and Gyro PACKET-------------");
	packet::print();
	Serial.print("Eulers: ");
	for(auto i = 0; i < 3; i++){
		Serial.print(euler[i]);
		Serial.print(" ");
	}
	Serial.print("\nYaw Pitch Roll: ");
	for (auto i = 0; i < 3; i++){
		Serial.print(yaw_pitch_roll[i]);
		Serial.print(" ");
	}
	Serial.println("");
	Serial.println("-----------Acceleration and Gyro PACKET END-----------");
}



//Spectrometer Packet

packets::spectrometer_packet::spectrometer_packet() {
	this->type = packets::SPECTROMETER;
}

packets::spectrometer_packet::spectrometer_packet(uint16_t send_addr, uint16_t dest_addr, uint8_t gate_addr,
	uint16_t pckt_id, uint8_t sensor_id, float channel_vals_in[]) {
	this->sender_address = send_addr;
	this->destination_address = dest_addr;
	this->network_gateway_address = gate_addr;
	this->type = packets::SPECTROMETER;
	this->id = pckt_id;
	memcpy(this->channel_values, channel_vals_in, sizeof(this->channel_values));
	this->size = sizeof(*this);
}

void packets::spectrometer_packet::set_channel_values(float vals[packets::spectrometer_packet::ARR_SIZE]) {
	memcpy(this->channel_values, vals, this->ARR_SIZE);
}

uint8_t* packets::spectrometer_packet::serialize() {
	static_assert(sizeof(float) == 4, "FLOAT SIZE ERROR: Not Equal to 4 Bytes, CANNOT SERIALIZE");
	uint8_t* return_buffer = packet::serialize();
	
	uint32_t channels32[this->ARR_SIZE] = {htonf(this->channel_values[0]),
											htonf(this->channel_values[1]),
											htonf(this->channel_values[2]),
											htonf(this->channel_values[3]),
											htonf(this->channel_values[4]),
											htonf(this->channel_values[5])
											};
	
	//convert eulers to bytes and add to the tail buffer
	size_t buffer_start_pos = 0;
	uint8_t conv8_float[4];
	for (size_t channel_it = 0; channel_it < this->ARR_SIZE; channel_it++) {
		conv8_float[0] = (channels32[channel_it] >> 24) & 0x00FF;
		conv8_float[1] = (channels32[channel_it] >> 16) & 0x00FF;
		conv8_float[2] = (channels32[channel_it] >> 8) & 0x00FF;
		conv8_float[3] = channels32[channel_it];
		return_buffer[packet::minimum_packet_size + 1 + buffer_start_pos] = conv8_float[0];
		return_buffer[packet::minimum_packet_size + 2 + buffer_start_pos] = conv8_float[1];
		return_buffer[packet::minimum_packet_size + 3 + buffer_start_pos] = conv8_float[2];
		return_buffer[packet::minimum_packet_size + 4 + buffer_start_pos] = conv8_float[3];
		buffer_start_pos += 4;
	}

	return return_buffer;
}


void packets::spectrometer_packet::deserialize(uint8_t* packet) {
	packet::deserialize(packet);

	//convert channel values from bytes to floats 
	uint8_t buffer_start_pos = 0;
	uint32_t cov_bytes = 0;
	for (size_t channel_it = 0; channel_it < this->ARR_SIZE; channel_it++) {
		cov_bytes = packet[packet::minimum_packet_size + 4 + buffer_start_pos] |
			(uint32_t)packet[packet::minimum_packet_size + 3 + buffer_start_pos] << 8 |
			(uint32_t)packet[packet::minimum_packet_size + 2 + buffer_start_pos] << 16 |
			(uint32_t)packet[packet::minimum_packet_size + 1 + buffer_start_pos] << 24;
		this->channel_values[channel_it] = ntohf(cov_bytes);
		buffer_start_pos += 4;
	}
}



void packets::spectrometer_packet::print() {
	Serial.println("-------------Spectrometer PACKET-------------");
	packet::print();
	Serial.print("Channel Values[R,S,T,U,V,W]: ");
	for (size_t i = 0; i < this->ARR_SIZE - 1; i++) {
		Serial.print('[');
		Serial.print(this->channel_values[i]);
		Serial.print("],");
	}
	Serial.print('[');
	Serial.print(this->channel_values[this->ARR_SIZE-1]);
	Serial.println(']');
	Serial.println("-----------Spectrometer PACKET END-----------");
}

