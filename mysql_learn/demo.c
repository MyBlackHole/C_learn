#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 3306

int main(int argc, char **argv)
{
	mysql_library_init(0, NULL, NULL);
	MYSQL *mysql = mysql_init(NULL);
	char *host_name = "127.0.0.1"; // set your mysql host
	char *user_name = "root"; // set your user_name
	char *password = "123456"; // set your password
	char *db_name = "test"; // set your databasename
	int port_num = PORT; // set your mysql port
	char *socket_name = NULL;
	MYSQL_RES *result;
	int status = 0;
	/* connect to server with the CLIENT_MULTI_STATEMENTS option */
	if (mysql_real_connect(mysql, host_name, user_name, password, db_name,
			       port_num, socket_name,
			       CLIENT_MULTI_STATEMENTS) == NULL) {
		printf("mysql_real_connect() failed\n");
		mysql_close(mysql);
		exit(1);
	}

	/* execute multiple statements */
	status = mysql_query(mysql, "DROP TABLE IF EXISTS test_table;\
                      CREATE TABLE test_table(id INT);\
                      INSERT INTO test_table VALUES(10);\
                      UPDATE test_table SET id=20 WHERE id=10;\
                      SELECT * FROM test_table;\
                      DROP TABLE test_table");
	if (status) {
		printf("Could not execute statement(s)");
		mysql_close(mysql);
		exit(0);
	}

	/* process each statement result */
	do {
		/* did current statement return data? */
		result = mysql_store_result(mysql);
		if (result) {
			/* yes; process rows and free the result set */
			// process_result_set(mysql, result);
			mysql_free_result(result);
		} else /* no result set or error */
		{
			if (mysql_field_count(mysql) == 0) {
				printf("%lld rows affected\n",
				       mysql_affected_rows(mysql));
			} else /* some error occurred */
			{
				printf("Could not retrieve result set\n");
				break;
			}
		}
		/* more results? -1 = no, >0 = error, 0 = yes (keep looping) */
		status = mysql_next_result(mysql);
		if (status > 0) {
			printf("Could not execute statement\n");
		}
	} while (status == 0);

	mysql_close(mysql);
}
