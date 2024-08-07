#include "LoggerStruct.h"

#include <stdlib.h>

void logger_set_next_logger_default(struct Logger *logger,
				    struct Logger *next_logger)
{
	if (NULL == logger)
		return;
	logger->next_logger = next_logger;
}

void logger_log_message_default(struct Logger *logger, int level,
				const char *message)
{
	if (NULL == logger)
		return;
	if (logger->level <= level) {
		if (NULL != logger->write)
			logger->write(logger, message);
	}
	if (NULL != logger->next_logger &&
	    NULL != logger->next_logger->log_message) {
		logger->next_logger->log_message(logger->next_logger, level,
						 message);
	}
}
