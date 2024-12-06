#include "int-vector.h"
#include "../base.h"
#include <stdio.h>
#include <stdlib.h>

IntVector* create_int_vector(const u64 capacity, CompareCallback compare_ints) {
	IntVector* vector = malloc(sizeof(IntVector));
	vector->capacity = capacity;
	vector->length = 0;
	vector->ints = malloc(vector->capacity * sizeof(i64));
	vector->compare_ints = compare_ints;
	vector->sorted = true;
	return vector;
}

static i64 last_element_in_int_vector(const IntVector* vector) {
	return vector->ints[vector->length - 1];
}

static bool int_vector_full(const IntVector* vector) {
	return vector->capacity == vector->length;
}

static bool int_vector_empty(const IntVector* vector) {
	return !vector->length;
}

void push_int_into_vector(IntVector* vector, const i64 integer) {
	if (int_vector_full(vector)) {
		vector->capacity *= 2;
		vector->ints = realloc(vector->ints, vector->capacity * sizeof(i64));
		if (vector->ints == NULL)
			print_error_then_exit(MEMORY_ALLOCATION_FAILED);
	}
	vector->ints[vector->length] = integer;
	if (
		int_vector_empty(vector) == false &&
		vector->sorted &&
		last_element_in_int_vector(vector) > integer
	)
		vector->sorted = false;
	vector->length++;
}

static void swap_two_ints_in_vector(IntVector* vector, u64 i, u64 j) {
	i64 tmp = vector->ints[i];
	vector->ints[i] = vector->ints[j];
	vector->ints[j] = tmp;
}

void sort_int_vector(IntVector* vector) {
	for (u64 i = 0; i < vector->length - 1; i++) {
		bool swapped = false;
		for (u64 j = 0; j < vector->length - i - 1; j++) {
			if (vector->compare_ints(vector->ints[j], vector->ints[j + 1])) {
				swap_two_ints_in_vector(vector, j, j + 1);
				swapped = true;
			}
		}
		if (swapped == false) break;
	}
	vector->sorted = true;
}

void print_int_vector(const IntVector* vector) {
	for (u64 i = 0; i < vector->length; i++)
		printf("%lu ", vector->ints[i]);
	printf("\n");
}

u32 get_frequency_of_int(const IntVector* vector, i64 integer) {
	u32 frequency = 0;

	if (vector->sorted) {
		for (
			u32 i = 0;
			i < vector->length && integer >= vector->ints[i];
			i++
		)
			if (vector->ints[i] == integer) frequency++; 
	} else {
		for (u32 i = 0; i < vector->length; i++)
			if (vector->ints[i] == integer) frequency++; 
	}
	return frequency;
}

bool is_decreasing_int_vector(const IntVector* vector, i64* failed_index) {
	for (u32 i = 0; i < vector->length - 1; i++)
		if (vector->ints[i] > vector->ints[i + 1]) {
			if (failed_index != NULL) *failed_index = i + 1;
			return false;
		}
	if (failed_index != NULL) *failed_index = -1;
	return true;
}

bool is_increasing_int_vector(const IntVector* vector, i64* failed_index) {
	for (u32 i = 0; i < vector->length - 1; i++)
		if (vector->ints[i] < vector->ints[i + 1]) {
			if (failed_index != NULL) *failed_index = i + 1;
			return false;
		}
	if (failed_index != NULL) *failed_index = -1;
	return true;
}

void empty_int_vector(IntVector* vector) {
	if (vector) {
		vector->length = 0;
		vector->sorted = true;
	}
}

void destroy_int_vector(IntVector* vector) {
	if (vector) {
		if (vector->ints) free(vector->ints);
		free(vector);
	}
}

void parse_string_to_int_vector(IntVector* vector, string str) {
	string next;
	i64 number;

	number = strtol(str, &next, 10);
	push_int_into_vector(vector, number);

	while (next[0] != '\0') {
		number = strtol(next, &next, 10);
		push_int_into_vector(vector, number);
	}
}

void remove_int_from_vector(IntVector* vector, u32 index) {
	if (index >= vector->length) {
		printf("Error: Our of bounds deletion\n");
		exit(1);
	}
	for (u32 i = index; i < vector->length - 1; i++) {
		vector->ints[i] = vector->ints[i + 1];
	}
	vector->length--;
}

IntVector* copy_int_vector(const IntVector* vector) {
	IntVector* new_vector =
		create_int_vector(vector->capacity, vector->compare_ints);
	new_vector->length = vector->length;
	for (u64 i = 0; i < new_vector->length; i++)
		new_vector->ints[i] = vector->ints[i];
	new_vector->sorted = new_vector->sorted;
	return new_vector;
}
