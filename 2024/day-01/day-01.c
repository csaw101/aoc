// 🎄 Day 1 Advent of Code 🎄

#include <stdlib.h>
#include <string.h>
#include "../../base/int-vector/int-vector.h"
#include "../../base/base.h"
#include "day-01.h"

// will be used by the sorting function (ascending)
static bool int_greater_than(const i64 a, const i64 b) {
	return a > b;
}

State* initialize_state(void) {
	State* state = malloc(sizeof(State));
	// create two empty vectors
	state->left_list = create_int_vector(2, int_greater_than);
	state->right_list = create_int_vector(2, int_greater_than);
	return state;
}

static void parse_line(const string line, State* state) {
	// parse both numbers
	string first_non_digit;
	i64 first_number = strtol(line, &first_non_digit, 10);
	i64 second_number = strtol(first_non_digit, NULL, 10);

	// push numbers into their respective vectors
	push_int_into_vector(state->left_list, first_number);
	push_int_into_vector(state->right_list, second_number);
}

void process_file(string file_name, State* state) {
	// read entire input file to a string
	string file_string = read_file_into_string(file_name);
	// tokenize the file string into lines, parse every line and update the
	// state
	map_lines_to_callback(file_string, (MapLineCallback) parse_line, state);
}

// Part 1
u64 calculate_total_distance(IntVector* left_list, IntVector* right_list) {
	sort_int_vector(left_list);
	sort_int_vector(right_list);

	u64 sum = 0;
	for (u32 i = 0; i < left_list->length; i++)
		sum += (u64) labs(left_list->ints[i] - right_list->ints[i]);
	return sum;
}

// Part 2
u64 calculate_similarity_score(
	const IntVector* left_list,
	const IntVector* right_list
) {
	u64 similarity_score = 0;
	for (u32 i = 0; i < left_list->length; i++)
		similarity_score +=
			(u64) left_list->ints[i] *
			get_frequency_of_int(right_list, left_list->ints[i]);
	return similarity_score;
}
