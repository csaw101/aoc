#ifndef STRING_VECTOR_H
#define STRING_VECTOR_H

#include "../types.h"

typedef bool (*CompareCallback) (void *, void *);

typedef struct StringVector {
	string* strings;
	u64 capacity;
	u64 size;
	CompareCallback compare;
} StringVector;

StringVector* create_string_vector(const u64 capacity);
void push_string_into_vector(StringVector* vector, const string new_string);
void print_string_vector(const StringVector* vector);

#endif // STRING_VECTOR_H
