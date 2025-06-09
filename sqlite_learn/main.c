#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
	printf("--------------------\n");
	printf("%s\n", (char *)data);
	printf("%d rows returned\n", argc);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	return 0;
}

int create_table()
{
	sqlite3 *db;
	int rc;
	char *err_msg = 0;
	char *data =
		"CREATE TABLE IF NOT EXISTS people (id INTEGER PRIMARY KEY, name TEXT, age INTEGER)";

	// rc = sqlite3_config(SQLITE_CONFIG_SERIALIZED);

	rc = sqlite3_open("test.db", &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Can't open database: %s\n",
			sqlite3_errmsg(db));
		return EXIT_FAILURE;
	}

	rc = sqlite3_exec(
		db,
		"CREATE TABLE IF NOT EXISTS people (id INTEGER PRIMARY KEY, name TEXT, age INTEGER)",
		callback, (void *)data, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		return EXIT_FAILURE;
	}
	sqlite3_close(db);

	return EXIT_SUCCESS;
}

int insert_data()
{
	sqlite3 *db;
	char *sql = "INSERT INTO people (name, age) VALUES (?,?)";
	sqlite3_stmt *stmt;
	int rc;
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n",
			sqlite3_errmsg(db));
		return EXIT_FAILURE;
	}
	sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

	/* bind the parameters */
	sqlite3_bind_text(stmt, 1, "John", -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, 25);

	/* execute the statement */
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		return EXIT_FAILURE;
	}

	/* reset the statement */
	sqlite3_reset(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return EXIT_SUCCESS;
}

int select_data()
{
	sqlite3 *db;
	int rc;
	char *data = "SELECT * FROM people";
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n",
			sqlite3_errmsg(db));
		return EXIT_FAILURE;
	}
	char *err_msg = 0;
	rc = sqlite3_exec(db, "SELECT * FROM people", callback, (void *)data,
			  &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		return EXIT_FAILURE;
	}
	sqlite3_close(db);
	return EXIT_SUCCESS;
}

int update_data()
{
	sqlite3 *db;
	int rc;
	char *data = "UPDATE people SET age = 30 WHERE name = 'John'";
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n",
			sqlite3_errmsg(db));
		return EXIT_FAILURE;
	}
	char *err_msg = 0;
	rc = sqlite3_exec(db, "UPDATE people SET age = 30 WHERE name = 'John'",
			  callback, (void *)data, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		return EXIT_FAILURE;
	}
	sqlite3_close(db);
	return EXIT_SUCCESS;
}

int delete_data()
{
	sqlite3 *db;
	int rc;
	char *data = "DELETE FROM people";
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n",
			sqlite3_errmsg(db));
		return EXIT_FAILURE;
	}
	char *err_msg = 0;
	rc = sqlite3_exec(db, "DELETE FROM people", callback, (void *)data,
			  &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		return EXIT_FAILURE;
	}
	sqlite3_close(db);
	return EXIT_SUCCESS;
}

int delete_table()
{
	sqlite3 *db;
	int rc;
	char *data = "DROP TABLE IF EXISTS people";
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n",
			sqlite3_errmsg(db));
		return EXIT_FAILURE;
	}
	char *err_msg = 0;
	rc = sqlite3_exec(db, "DROP TABLE people", callback, (void *)data,
			  &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		return EXIT_FAILURE;
	}
	sqlite3_close(db);
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	int ret = EXIT_SUCCESS;
	ret = create_table()	    ?:
		      insert_data() ?:
		      select_data() ?:
		      delete_data() ?:
				      delete_table();
	return ret;
}
