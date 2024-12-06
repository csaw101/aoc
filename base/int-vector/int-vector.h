#ifndef INT_VECTOR_H
#define INT_VECTOR_H

#include "../types.h"

typedef bool (*CompareCallback) (i64, i64);

typedef struct IntVector {
	i64* ints;
	u64 length;
	u64 capacity;
	bool sorted;
	CompareCallback compare_ints;
} IntVector;

IntVector* create_int_vector(const u64 capacity, CompareCallback compare_ints);
void push_int_into_vector(IntVector* vector, const i64 integer);
void print_int_vector(const IntVector* vector);
void sort_int_vector(IntVector* vector);
u32 get_frequency_of_int(const IntVector* vector, i64 integer);
bool is_decreasing_int_vector(const IntVector* vector, i64* failed_index);
bool is_increasing_int_vector(const IntVector* vector, i64* failed_index);
void empty_int_vector(IntVector* vector);
void parse_string_to_int_vector(IntVector* vector, string str);
void remove_int_from_vector(IntVector* vector, u32 index);
void destroy_int_vector(IntVector* vector);

#endif // INT_VECTOR_H
