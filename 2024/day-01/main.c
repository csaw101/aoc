// 🎄 Day 1 Advent of Code 🎄

#include <stdio.h>
#include "day-01.h"

int main(void) {
	// both vectors will be in a state variable that is continuously updated
	// when every line is parsed
	State* state = initialize_state();
	process_file("./2024/day-01/input.txt", state);

	u64 total_distance =
		calculate_total_distance(state->left_list, state->right_list);
	u64 similarity_score =
		calculate_similarity_score(state->left_list, state->right_list);
	printf("Total distance: %lu\n", total_distance); // 2815556 
	printf("Similarity score: %lu\n", similarity_score); // 23927637

	return 0;
}
