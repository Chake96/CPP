#pragma once


#ifndef _PACKETS_h
#define _PACKETS_h

#include <packet.h>
#include <plan.h>

/*
	To-do ->
	tranform into templates
	factory for packet.h
*/


namespace packets {
	//error message packet


	/*to-do convert to ENUM Class, need to static_cast to int conversions */
	enum packet_types {
		ERROR = 0,
		COMMUNICATION = 1,
		ULTRASONIC = 2,
		IR_RANGE = 3,
		SPECTROMETER = 4,
		ACCEL_GYRO = 5,
		COLOR = 6,
		LIGHT = 7,
		UV_LIGHT = 8,
		PLAN = 9,
		NUMBER = 10
	};

	class number_packet :virtual public packet {
		private: 
			uint8_t* data;
		public:
			number_packet();
			number_packet(uint16_t sender_address, uint16_t destination_address, uint8_t net_gateway_address,
				uint16_t pckt_id, uint8_t* data);
			inline void set_data(uint8_t* data);
			const uint8_t* get_data();
			virtual uint8_t* serialize();
			virtual void deserialize(uint8_t* packet);
			void print();
	};

	class plan_packet:virtual public packet {
		private:
			plan _plan;
		public:
			static constexpr uint8_t MAX_NUMBER_COMMANDS = 8; //max # of commands that can fit into a single packet, does not get serialized
			
			plan_packet();
			plan_packet(uint16_t sender_address, uint16_t destination_address, uint8_t net_gateway_address,
				uint16_t pckt_id, const plan& plan);
			//plan_packet operator=(plan_packet packet);
			void set_plan(const plan& plan_in);
			plan get_plan();

			virtual uint8_t* serialize();
			void deserialize(uint8_t* packet);
			void print();

	};

	class error_packet:virtual public packet{
		private:
			char* data = nullptr;
		public:
			error_packet();
			error_packet(uint16_t sender_address, uint16_t destination_address, uint8_t net_gateway_address,
				uint16_t pckt_id, char* data);
			void set_data(char* data);
			const char* get_data();
			uint8_t* serialize();
			void deserialize(uint8_t* packet);
			void print();
	};


	class comm_packet:virtual public packet {
		private:
			char* data = nullptr;
		public:
			comm_packet();
			comm_packet(uint16_t sender_address, uint16_t destination_address, uint8_t net_gateway_address,
				uint16_t pckt_id, char* data);
			const char* get_data();
			virtual void set_data(char* data_in);
			virtual uint8_t* serialize();
			virtual void deserialize(uint8_t* packet);
			void print();
	};
	
	class ultrasonic_packet:virtual public packet {
	private:
		uint8_t sensor_id;
		uint16_t distance;
	public:
		ultrasonic_packet();
		ultrasonic_packet(uint16_t sender_address, uint16_t destination_address, uint8_t net_gateway_address,
			uint16_t pckt_id, uint8_t id, uint16_t distance);
		
		void set_data(const uint8_t id,const uint16_t distance);
		void set_sensor_id(const uint8_t sensor_id);
		void set_distance(uint16_t distance);

		const uint8_t get_sensor_id();
		const uint16_t get_distance();
		const pair<uint8_t, uint16_t> get_data();

		uint8_t* serialize();
		void deserialize(uint8_t* packet);
		void print();
	};

	class ir_packet :virtual public packet {
		private:
			uint8_t sensor_id;
			uint16_t distance;
		public:
			ir_packet();
			ir_packet(uint16_t sender_address, uint16_t destination_address, uint8_t net_gateway_address,
				uint16_t pckt_id, uint8_t id, uint16_t distance);

			void set_data(const uint8_t id, const uint16_t distance);
			void set_sensor_id(const uint8_t sensor_id);
			void set_distance(uint16_t distance);

			const uint8_t get_sensor_id();
			const uint16_t get_distance();
			const pair<uint8_t, uint16_t> get_data();

			uint8_t* serialize();
			void deserialize(uint8_t* packet);
			void print();
	};

	class spectrometer_packet :virtual public packet {
		private:
			static constexpr size_t ARR_SIZE = 6;
			uint8_t sensor_id;
			float channel_values[ARR_SIZE];

		public:
			spectrometer_packet();
			spectrometer_packet(uint16_t sender_address, uint16_t destination_address, uint8_t net_gateway_address,
				uint16_t pckt_id, uint8_t id, float sensor_values[ARR_SIZE]);

			void set_channel_values(float sensor_values[ARR_SIZE]);
			void set_sensor_id(const uint8_t sensor_id);
			void set_temperature(const int8_t temp);


			const uint8_t get_sensor_id();
			const int8_t get_temperature();
			float* get_sensor_vals();

			uint8_t* serialize();
			void deserialize(uint8_t* packet);
			void print();
	};


	class accel_gyro_packet:virtual public packet {
	private:
		static constexpr size_t array_size = 3;
		float euler[array_size] = {0, 0, 0}; //psi, theta, phi
		float yaw_pitch_roll[array_size] = {0, 0, 0};
	public:
		accel_gyro_packet();
		accel_gyro_packet(uint16_t sender_address, uint16_t destination_address, uint8_t net_gateway_address,
			uint16_t pckt_id, float* eulers, float* ypr);
		void set_data(const float eulers[array_size], const float yaw_pitch_roll[array_size]);
		void set_euler(const float euler[array_size]);
		void set_yaw_ptch_roll(float ypr[array_size]);

		const float* get_euler();
		const float* get_yaw_ptch_roll();
		const pair<float[array_size], float[array_size]> get_data();

		uint8_t* serialize();
		void deserialize(uint8_t* packet);
		void print();
	};
		
}

#endif