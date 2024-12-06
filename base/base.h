#ifndef BASE_H
#define BASE_H

#include "types.h"

// Strings
string duplicate_string(const string source);

typedef void (*MapLineCallback) (const string line, void* state);
void map_lines_to_callback(
	const string str,
	const MapLineCallback callback,
	void* state
);

// Files
string read_file_into_string(const string file_name);

// Errors
enum Error {
	MEMORY_ALLOCATION_FAILED
};

void print_error_then_exit(enum Error error);

#endif // BASE_H
