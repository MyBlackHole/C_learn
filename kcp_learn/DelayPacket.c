#include "DelayPacket.h"

#include <stdlib.h>
#include <string.h>

#include "ikcp.h"

DelayPacket *createDelayPacket(int size, const void *src)
{
	struct DelayPacket *delayPacket = NULL;
	delayPacket = malloc(sizeof(*delayPacket));
	delayPacket->_ptr = malloc(sizeof(char) * size);
	delayPacket->_size = size;
	if (src) {
		memcpy(delayPacket->_ptr, src, size);
	}
	return delayPacket;
}

unsigned char *delayPacketGetPtr(DelayPacket *delayPacket)
{
	return delayPacket->_ptr;
}

int delayPacketGetSize(DelayPacket *delayPacket)
{
	return delayPacket->_size;
}

IUINT32 delayPacketGetTs(DelayPacket *delayPacket)
{
	return delayPacket->_ts;
};

void delayPacketSetTs(DelayPacket *delayPacket, IUINT32 ts)
{
	delayPacket->_ts = ts;
};

void destroy(DelayPacket *delayPacket)
{
	if (!delayPacket) {
		return;
	}
	if (!delayPacket->_ptr) {
		free(delayPacket->_ptr);
	}
	free(delayPacket);
}
