
#include "munit.h"

static MunitResult test_example(const MunitParameter params[], void *user_data)
{
	(void)params;
	(void)user_data;
	munit_assert(0 != 1);

	// int random_int;
	// double random_dbl;
	// munit_uint8_t data[5];

	// random_int = munit_rand_int_range(128, 4096);
	// munit_assert_int(random_int, >=, 128);
	// munit_assert_int(random_int, <=, 4096);

	// random_dbl = munit_rand_double();
	// munit_assert_double(random_dbl, >=, 0.0);
	// munit_assert_double(random_dbl, <=, 1.0);

	// munit_rand_memory(sizeof(data), data);
	return MUNIT_OK;
}

MunitSuite _main_suites[64];

static MunitTest test[] = {
	{ (char *)"/example", test_example, NULL, NULL, MUNIT_TEST_OPTION_NONE,
	  NULL },
	// {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite suite = { (char *)"", test, NULL, 1,
			    MUNIT_SUITE_OPTION_NONE };

#include <stdlib.h>
int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
	// MunitSuite suite = {(char *)"", NULL, _main_suites, 1,
	//                     MUNIT_SUITE_OPTION_NONE};
	return munit_suite_main(&suite, (void *)"black", argc, argv);
}
