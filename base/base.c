#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "base.h"

// Strings
string duplicate_string(const string source) {
	string destination = malloc(strlen(source) + 1);
	if (destination == NULL)
		print_error_then_exit(MEMORY_ALLOCATION_FAILED);
	strcpy(destination, source);
	return destination;
}

void map_lines_to_callback(
	const string str,
	const MapLineCallback callback,
	void* state
) {
	string line = strtok(str, "\n");
	while (line) {
		callback(line, state);
		line = strtok(NULL, "\n");
	}
}

// Files
string read_file_into_string(const string file_name) {
    FILE *stream;
    i64 fileLength;
    char *buffer;

    stream = fopen(file_name, "r");

    fseek(stream, 0, SEEK_END);
    fileLength = ftell(stream);
    rewind(stream);

    buffer = malloc((u64) fileLength * sizeof(char) + 1);
    buffer[fileLength] = '\0';
    fread(buffer, 1, (u64) fileLength, stream);
    fclose(stream);

    return buffer;
}

// Errors
void print_error_then_exit(enum Error error) {
	if (error == MEMORY_ALLOCATION_FAILED)
		printf("Memory allocation failed\n");
	exit(1);
}
