#ifndef __DelayPacket_H__
#define __DelayPacket_H__

#include "ikcp.h"

typedef struct DelayPacket {
	unsigned char *_ptr;
	int _size;
	IUINT32 _ts;
} DelayPacket;

// class DelayPacket {
// public:
//   virtual ~DelayPacket() {
//     if (_ptr)
//       delete[] _ptr;
//     _ptr = NULL;
//   }

//   DelayPacket(int size, const void *src = NULL) {
//     _ptr = new unsigned char[size];
//     _size = size;
//     if (src) {
//       memcpy(_ptr, src, size);
//     }
//   }

//   unsigned char *ptr() { return _ptr; }
//   const unsigned char *ptr() const { return _ptr; }

//   int size() const { return _size; }
//   IUINT32 ts() const { return _ts; }
//   void setts(IUINT32 ts) { _ts = ts; }

// protected:
//   unsigned char *_ptr;
//   int _size;
//   IUINT32 _ts;
// };

DelayPacket *createDelayPacket(int size, const void *src);

unsigned char *delayPacketGetPtr(DelayPacket *delayPacket);

int delayPacketGetSize(DelayPacket *delayPacket);

IUINT32 delayPacketGetTs(DelayPacket *delayPacket);

void delayPacketSetTs(DelayPacket *delayPacket, IUINT32 ts);

void destroy(DelayPacket *);
#endif
