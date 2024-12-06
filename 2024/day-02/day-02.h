// 🎄 Day 2 Advent of Code: Red-Nosed Reports 🎄

#include "../../base/int-vector/int-vector.h"

typedef struct State {
	IntVector* current_report;
	u32 safe_levels; // Part 1
	u32 safe_levels_tolerate_one; // Part 2
} State;

State* initialize_state(void);
void process_file(string file_name, State* state);
void destroy_state(State* state);
