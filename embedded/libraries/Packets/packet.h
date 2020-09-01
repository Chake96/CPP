#pragma once

#include <pair.h>
#include <stdint.h>
#include <stddef.h>
#include <HardwareSerial.h>
// packet.h

typedef uint8_t byte;

/*to do
implement rule of three
copy constructor makes sense given that types of a packet may misalign
*/

template<typename T>
struct is_pointer { static const bool value = false; };

template<typename T>
struct is_pointer<T*> { static const bool value = true; };

static constexpr size_t RADIO_PACKET_TYPE_INDEX = 0;

#ifndef _PACKET_h
#define _PACKET_h


class packet {
	protected:
		uint16_t sender_address;
		static constexpr uint8_t max_frame_size = 61U*sizeof(byte);
		static constexpr uint8_t minimum_packet_size = 8;
	public:
		packet(){};
		virtual ~packet(){};
		uint8_t type; //relates to packet_types enum
		uint16_t destination_address;
		uint8_t network_gateway_address;
		uint16_t id;
		size_t size = sizeof(packet);
		uint8_t max_size();
		uint16_t get_sender_addr();
		
		virtual void print() {
			Serial.print("Packet Type: ");
			Serial.println(this->type);
			Serial.print("Sender Address: ");
			Serial.println(this->sender_address);
			Serial.print("Destination Address: ");
			Serial.println(this->destination_address);
			Serial.print("Gateway Address: ");
			Serial.println(this->network_gateway_address);
			Serial.print("Packet ID: ");
			Serial.println(this->id);
			Serial.print("Packet Size: ");
			Serial.println(this->size);
		}

		//to-do finish bitshifting on serializing
		virtual uint8_t* serialize() {
			uint8_t* serialized_pckt = new uint8_t;
			uint8_t type = static_cast<uint8_t>(this->type);
			uint8_t id_msb = static_cast<uint8_t>(id >> 8 & 0x00FF);
			uint8_t id_lsb = static_cast<uint8_t>(id);
			uint8_t size = static_cast<uint8_t>(this->size);
			uint8_t send_addr_msb = static_cast<uint8_t>(sender_address >> 8 & 0x00FF);
			uint8_t send_addr_lsb = static_cast<uint8_t>(sender_address);
			uint8_t dest_addr_msb = static_cast<uint8_t>(destination_address >> 8 & 0x00FF);
			uint8_t dest_addr_lsb = static_cast<uint8_t>(destination_address);
			uint8_t gate_way_addr = this->network_gateway_address;

			serialized_pckt[0] = type;
			serialized_pckt[1] = size;
			serialized_pckt[2] = id_msb;
			serialized_pckt[3] = id_lsb;
			serialized_pckt[4] = send_addr_msb;
			serialized_pckt[5] = send_addr_lsb;
			serialized_pckt[6] = dest_addr_msb;
			serialized_pckt[7] = dest_addr_lsb;
			serialized_pckt[8] = gate_way_addr;

			return serialized_pckt;
		}

		virtual void deserialize(uint8_t* s_packet) {
			this->type = s_packet[0];
			this->size = s_packet[1];
			this->id = (s_packet[2] << 8) | s_packet[3];
			this->sender_address = (s_packet[4] << 8) | s_packet[5];
			this->destination_address= (s_packet[6] << 8) | s_packet[7];
			this->network_gateway_address = s_packet[8];
		}
};



inline uint8_t packet::max_size() {
	return this->max_frame_size;
}

inline uint16_t packet::get_sender_addr() {
	return this->sender_address;
}

#endif
