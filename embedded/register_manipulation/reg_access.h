#include <cstdint>

template<typename addr_type, typename reg_type, const addr_type address, const reg_type value>
class reg_access{
	public:
		static void reg_set(){
			*reinterpret_cast<volatile reg_type*>(address) = value;
		}

		static reg_type reg_get(){
			return *reinterpret_cast<volatile reg_type*>(address);
		}

		static void reg_or(){
			*reinterpret_cast<volatile reg_type*>(address) |= value;
		}

		//toggles the bit 
		static void bit_not(){
			*reinterpret_cast<volatile reg_type*>(address) ^= reg_type(1U) << value;
		}
		
		//clears bit by applying not-and to itself 
		static void clr_bit(){
			*reinterpret_cast<volatile reg_type*>(address) &= ~(reg_type(1U) << value);
		}

		static void set_bit(reg_type bit_n, bool in_value){
			*reinterpret_cast<volatile reg_type*>(address) ^= (!in_value ^ (address)) & (1UL << bit_n);
		}
};

