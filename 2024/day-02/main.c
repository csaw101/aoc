// 🎄 Day 2 Advent of Code: Red-Nosed Reports 🎄

#include <stdio.h>
#include "day-02.h"

int main(void) {
	State* state = initialize_state();
	process_file("./2024/day-02/input.txt", state);

	printf("%d\n", state->safe_levels); // 585
	printf("%d\n", state->safe_levels_tolerate_one); // 626

	destroy_state(state);

	return 0;
}
