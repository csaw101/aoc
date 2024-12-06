// 🎄 Day 1 Advent of Code 🎄

#include "../../base/int-vector/int-vector.h"

typedef struct State {
	IntVector* left_list;
	IntVector* right_list;
} State;

State* initialize_state(void);
void process_file(string file_name, State* state);
u64 calculate_total_distance(IntVector* left_list, IntVector* right_list);
u64 calculate_similarity_score(
	const IntVector* left_list,
	const IntVector* right_list
);
