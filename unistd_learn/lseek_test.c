#include "apue.h"
#include <fcntl.h>

int main(void) {
  // 控制该文件的读写位置
  //
  // SEEK_SET 参数offset 即为新的读写位置.
  // SEEK_CUR 以目前的读写位置往后增加offset 个位移量.
  // SEEK_END 将读写位置指向文件尾后再增加offset 个位移量. 当whence 值为SEEK_CUR
  // 或 SEEK_END 时, 参数offet 允许负值的出现.

  if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
    printf("cannot seek\n");
  else
    printf("seek ok\n");
  exit(0);
}
