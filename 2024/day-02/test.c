// 🎄 Day 2 Advent of Code: Red-Nosed Reports 🎄

#include <criterion/criterion.h>
#include "day-02.h"

State* state;

static void setup(void) {
	state = initialize_state();
	process_file("./2024/day-02/test.txt", state);
}

Test(part_one, total_distance, .init=setup) {
	cr_expect_eq(state->safe_levels, 2);
}

Test(part_two, similarity_score, .init=setup) {
	cr_expect_eq(state->safe_levels_tolerate_one, 4);
}
