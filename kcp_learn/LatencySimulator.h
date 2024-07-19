#ifndef __LatencySimulator_H__
#define __LatencySimulator_H__

#include "Random.h"
#include "ikcp.h"
#include <tbox/container/vector.h>

typedef struct LatencySimulator {
	int tx1;
	int tx2;

	IUINT32 current;
	int lostrate;
	int rttmin;
	int rttmax;
	int nmax;
	tb_vector_ref_t p12;
	tb_vector_ref_t p21;
	Random *r12;
	Random *r21;

} LatencySimulator;

// lostrate: 往返一周丢包率的百分比，默认 10%
// rttmin：rtt最小值，默认 60
// rttmax：rtt最大值，默认 125
LatencySimulator *createLatencySimulator(int lostrate, int rttmin, int rttmax,
					 int nmax);

void destroyLatencySimulator(LatencySimulator *latencySimulator);

// 发送数据
// peer - 端点0/1，从0发送，从1接收；从1发送从0接收
void sendLatencySimulator(LatencySimulator *latencySimulator, int peer,
			  const void *data, int size);

// 清除数据
void clearLatencySimulator(LatencySimulator *latencySimulator);

// // 网络延迟模拟器
// // p12 p21:包列表
// class LatencySimulator {
// public:
//   virtual ~LatencySimulator() { clear(); }

//   // lostrate: 往返一周丢包率的百分比，默认 10%
//   // rttmin：rtt最小值，默认 60
//   // rttmax：rtt最大值，默认 125
//   LatencySimulator(int lostrate = 10, int rttmin = 60, int rttmax = 125,
//                    int nmax = 1000)
//       : r12(100), r21(100) {
//     current = iclock();
//     this->lostrate = lostrate / 2; // 上面数据是往返丢包率，单程除以2
//     this->rttmin = rttmin / 2;
//     this->rttmax = rttmax / 2;
//     this->nmax = nmax;
//     tx1 = tx2 = 0;
//   }

//   // 清除数据
//   void clear() {
//     DelayTunnel::iterator it;
//     for (it = p12.begin(); it != p12.end(); it++) {
//       delete *it;
//     }
//     for (it = p21.begin(); it != p21.end(); it++) {
//       delete *it;
//     }
//     p12.clear();
//     p21.clear();
//   }

//   // 发送数据
//   // peer - 端点0/1，从0发送，从1接收；从1发送从0接收
//   void send(int peer, const void *data, int size) {
//     if (peer == 0) {
//       tx1++;
//       if (r12.random() < lostrate)
//         return;
//       if ((int)p12.size() >= nmax)
//         return;
//     } else {
//       tx2++;
//       if (r21.random() < lostrate)
//         return;
//       if ((int)p21.size() >= nmax)
//         return;
//     }
//     DelayPacket *pkt = new DelayPacket(size, data);
//     current = iclock();
//     IUINT32 delay = rttmin;
//     if (rttmax > rttmin)
//       delay += rand() % (rttmax - rttmin);
//     // 设置延迟时间
//     pkt->setts(current + delay);
//     if (peer == 0) {
//       p12.push_back(pkt);
//     } else {
//       p21.push_back(pkt);
//     }
//   }

//   // 接收数据
//   int recv(int peer, void *data, int maxsize) {
//     DelayTunnel::iterator it;
//     if (peer == 0) {
//       it = p21.begin();
//       if (p21.size() == 0)
//         return -1;
//     } else {
//       it = p12.begin();
//       if (p12.size() == 0)
//         return -1;
//     }
//     DelayPacket *pkt = *it;
//     current = iclock();
//     // 判断是否大于延迟时间
//     if (current < pkt->ts())
//       return -2;
//     if (maxsize < pkt->size())
//       return -3;
//     if (peer == 0) {
//       p21.erase(it);
//     } else {
//       p12.erase(it);
//     }
//     maxsize = pkt->size();
//     memcpy(data, pkt->ptr(), maxsize);
//     delete pkt;
//     return maxsize;
//   }

// public:
//   int tx1;
//   int tx2;

// protected:
//   IUINT32 current;
//   int lostrate;
//   int rttmin;
//   int rttmax;
//   int nmax;
//   typedef std::list<DelayPacket *> DelayTunnel;
//   DelayTunnel p12;
//   DelayTunnel p21;
//   Random r12;
//   Random r21;
// };
#endif
