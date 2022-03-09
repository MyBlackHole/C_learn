#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// SEEK_SET 参数offset 即为新的读写位置.
// SEEK_CUR 以目前的读写位置往后增加offset 个位移量.
// SEEK_END 将读写位置指向文件尾后再增加offset 个位移量. 当whence 值为SEEK_CUR
// 或 SEEK_END 时, 参数offet 允许负值的出现.
//  1) 欲将读写位置移到文件开头时:lseek(int fildes, 0, SEEK_SET);
//  2) 欲将读写位置移到文件尾时:lseek(int fildes, 0, SEEK_END);
//  3) 想要取得目前文件位置时:lseek(int fildes, 0, SEEK_CUR);

int main(int argc, char *argv[]) {
  int fd = 0;
  if (argc < 2) {
    fprintf(stderr, "<path>\n");
    exit(1);
  }

  fd = open(argv[1], O_RDONLY, 0600);
  lseek(fd, 1, SEEK_SET);

  // write(fd, "ok", 3);
  int n = 10;
  char *s = malloc(n);
  read(fd, s, n);
  printf("%s\n", s);

  close(fd);

  exit(0);
}
