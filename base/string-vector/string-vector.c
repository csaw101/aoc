#include "string-vector.h"
#include <stdlib.h>
#include <stdio.h>
#include "../base.h"

StringVector* create_string_vector(const u64 capacity) {
	StringVector* vector = malloc(sizeof(StringVector));
	vector->capacity = capacity;
	vector->size = 0;
	vector->strings = malloc(vector->capacity * sizeof(string));
	if (vector->strings == NULL)
		print_error_then_exit(MEMORY_ALLOCATION_FAILED);

	return vector;
}

void push_string_into_vector(StringVector* vector, const string new_string) {
	if (vector->capacity == vector->size) {
		vector->capacity *= 2;
		vector->strings = realloc(
			vector->strings,
			vector->capacity * sizeof(string)
		);
		if (vector->strings == NULL)
			print_error_then_exit(MEMORY_ALLOCATION_FAILED);
	}

	vector->strings[vector->size] = duplicate_string(new_string);
	vector->size++;
}

void print_string_vector(const StringVector* vector) {
	for (u64 i = 0; i < vector->size; i++)
		printf("%s\n", vector->strings[i]);
}
