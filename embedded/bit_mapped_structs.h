/*
this is a bit-field that replicates an 8-bit port register
it is portable only to 8-bit CPUs
*/

typedef struct struct_bit8_type{
	std::uint8_t bit0: 1;
	std::uint8_t bit1: 1;
	std::uint8_t bit2: 1;
	std::uint8_t bit3: 1;
	std::uint8_t bit4: 1;
	std::uint8_t bit5: 1;
	std::uint8_t bit6: 1;
	std::uint8_t bit7: 1;
}bit8_type;


//this register c-style union is helpful in representing the physical register
//the union allows for storing both the value and bit8_type in the same location
typedef union union_register_map_c{
	std::uint8_t value;
	bit8_type bits;
}register_map_c;

