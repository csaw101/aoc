// 🎄 Day 1 Advent of Code 🎄

#include <criterion/criterion.h>
#include "day-01.h"

State* state;

static void setup(void) {
	state = initialize_state();
	process_file("./2024/day-01/test.txt", state);
}

Test(part_one, total_distance, .init=setup) {
	u64 total_distance =
		calculate_total_distance(state->left_list, state->right_list);
	cr_expect_eq(total_distance, 11);
}

Test(part_two, similarity_score, .init=setup) {
	u64 similarity_score =
		calculate_similarity_score(state->left_list, state->right_list);
	cr_expect_eq(similarity_score, 31);
}
