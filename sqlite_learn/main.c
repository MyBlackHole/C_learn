#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char *argv[])
{
	sqlite3 *db;
	int rc;
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n",
			sqlite3_errmsg(db));
		return EXIT_FAILURE;
	}
	char *err_msg = 0;
	rc = sqlite3_exec(db, "CREATE TABLE people (name TEXT, age INTEGER)", 0, 0, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		return EXIT_FAILURE;
	}
	sqlite3_close(db);
	return EXIT_SUCCESS;
}
