// Plan.h

#ifndef _PLAN_h
#define _PLAN_h

#include <stdint.h>
#include <stddef.h>

enum command_options: uint8_t {
	STOP = 0,
	EXECUTE = 1,
	FORWARD = 2,
	REVERSE = 3,
	LEFT = 4,
	RIGHT = 5,
	SKIP_NEXT = 6, //skips the command, is injected into the command parser
	MOVE_TO_START = 7,
	MOVE_TO_GOAL = 8,
	GOAL_LAT = 9,
	GOAL_LNG = 10,
	TURN_TO_DEGREE = 11
};

/*usage
	instruction
*/
struct command {
	uint8_t type;
	float duration; //units of length, accurate up to 4 decimal places, 
					//issue in (de)serialization and sending through RF
};

//lots of potential memory leaks need to investigate with valgrind

class plan {
	private:
		command* commands = nullptr;
		uint16_t length = 0;
		command* last_command = commands;
	public:
		plan();
		//plan(uint16_t plan_length);
		//plan(uint16_t plan_length, command commands_list[]);

		void append(command& new_command);
		inline bool empty(){return this->length == 0;};
		const uint16_t get_length();
		command pop();
		const command& top();
		const command& get_command(uint16_t index);

		void print();
};


#endif

