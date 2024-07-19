#ifndef __Random_H__
#define __Random_H__
#include <tbox/container/vector.h>

typedef struct Random {
	int size;
	tb_vector_ref_t seeds;
} Random;

// // 均匀分布的随机数
// class Random {
// public:
//   Random(int size) {
//     this->size = 0;
//     seeds.resize(size);
//   }

//   int random() {
//     int x, i;
//     if (seeds.size() == 0)
//       return 0;
//     if (size == 0) {
//       for (i = 0; i < (int)seeds.size(); i++) {
//         seeds[i] = i;
//       }
//       size = (int)seeds.size();
//     }
//     i = rand() % size;
//     x = seeds[i];
//     seeds[i] = seeds[--size];
//     return x;
//   }

// protected:
//   int size;
//   std::vector<int> seeds;
// };

Random *createRandom(int size);

int getRandom(Random *random);

void destroyRandom(Random *random);
#endif
