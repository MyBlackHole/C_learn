#include <stdio.h>

#include "LoggerStruct.h"
#include "ctools.h"

static void write(struct Logger *logger, const char *message)
{
	printf("File::Logger: %s\n", message);
}

struct Logger *file_logger_create(int level)
{
	struct Logger *logger =
		(struct Logger *)calloc(1, sizeof(struct Logger));
	if (NULL == logger)
		return NULL;

	logger->level = level;
	logger->log_message = logger_log_message_default;
	logger->set_next_logger = logger_set_next_logger_default;
	logger->write = write;
	return logger;
}
