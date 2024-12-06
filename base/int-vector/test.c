#include <criterion/criterion.h>
#include "int-vector.h"

IntVector* vector;

// for ascending order sorting
static bool int_greater_than(i64 a, i64 b) {
	return a > b;
}

void setup(void) {
	vector = create_int_vector(2, int_greater_than);
}

Test(sort, sorted, .init=setup) {
	for (i32 i = 0; i <= 9; i++)
		push_int_into_vector(vector, i);

	sort_int_vector(vector);
	i64 sorted_vector[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	cr_expect_arr_eq(vector->ints, sorted_vector, 10 * sizeof(i64));
}

Test(sort, reverse, .init=setup) {
	for (i32 i = 9; i >= 0; i--)
		push_int_into_vector(vector, i);

	sort_int_vector(vector);
	i64 sorted_vector[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	cr_expect_arr_eq(vector->ints, sorted_vector, 10 * sizeof(i64));
}

Test(get_frequency, not_sorted, .init=setup) {
	for (i32 i = 9; i >= 0; i--)
		push_int_into_vector(vector, i);
	vector->sorted = false;

	cr_expect_eq(get_frequency_of_int(vector, -1), 0);
	cr_expect_eq(get_frequency_of_int(vector, 0), 1);
	cr_expect_eq(get_frequency_of_int(vector, 5), 1);
	cr_expect_eq(get_frequency_of_int(vector, 9), 1);
	cr_expect_eq(get_frequency_of_int(vector, 10), 0);
}

Test(get_frequency, sorted, .init=setup) {
	for (i32 i = 0; i <= 9; i++)
		push_int_into_vector(vector, i);
	vector->sorted = true;

	cr_expect_eq(get_frequency_of_int(vector, -1), 0);
	cr_expect_eq(get_frequency_of_int(vector, 0), 1);
	cr_expect_eq(get_frequency_of_int(vector, 5), 1);
	cr_expect_eq(get_frequency_of_int(vector, 9), 1);
	cr_expect_eq(get_frequency_of_int(vector, 10), 0);
}
