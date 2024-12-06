// 🎄 Day 2 Advent of Code: Red-Nosed Reports 🎄

#include <stdlib.h>
#include <stdio.h>
#include "../../base/int-vector/int-vector.h"
#include "../../base/base.h"
#include "day-02.h"

// can be used by the sorting function (ascending)
static bool int_greater_than(const i64 a, const i64 b) {
	return a < b;
}

State* initialize_state(void) {
	State* state = malloc(sizeof(State));
	state->current_report = create_int_vector(2, int_greater_than);
	state->safe_levels = 0;
	state->safe_levels_tolerate_one = 0;
	return state;
}

void destroy_state(State* state) {
	if (state) {
		destroy_int_vector(state->current_report);
		free(state);
	}
}

static bool differs_by_one_to_three(
	const IntVector* vector,
	i64* bad_level_index
) {
	i64 difference;
	for (u32 i = 0; i < vector->length - 1; i++) {
		difference = labs(vector->ints[i] - vector->ints[i + 1]);
		if (difference > 3 || difference < 1) {
			if (bad_level_index != NULL) *bad_level_index = i + 1;
			return false;
		}
	}
	if (bad_level_index != NULL) *bad_level_index = -1;
	return true;
}

// Part 1
static bool safe_report(IntVector* report) {
	bool in_range = differs_by_one_to_three(report, NULL);
	bool decreasing = is_decreasing_int_vector(report, NULL);
	bool increasing = is_increasing_int_vector(report, NULL);

	return in_range && (decreasing || increasing);
}

// Part 2
// TODO: very poor implementation, try to remove an int only at the first
// inconsistency or maybe you need to remove two consecutive ints?
static bool safe_report_with_one_bad_level(IntVector* report) {
	if (safe_report(report)) return true;
	for (u32 i = 0; i < report->length; i++) {
		IntVector* new_report = copy_int_vector(report);
		remove_int_from_vector(new_report, i);
		bool safe = safe_report(new_report);
		destroy_int_vector(new_report);
		if (safe) return true;
	}
	return false;
}

static void parse_and_check_safe_levels(
	const string line,
	State* state
) {
	parse_string_to_int_vector(state->current_report, line);

	// Part 1
	if (safe_report(state->current_report))
		state->safe_levels++;

	// Part 2
	if (safe_report_with_one_bad_level(state->current_report))
		state->safe_levels_tolerate_one++;

	empty_int_vector(state->current_report);
}

void process_file(string file_name, State* state) {
	// read entire input file to a string
	string file_string = read_file_into_string(file_name);
	// tokenize the file string into lines, parse every line and update the
	// state
	map_lines_to_callback(
		file_string,
		(MapLineCallback) parse_and_check_safe_levels,
		state
	);
}
