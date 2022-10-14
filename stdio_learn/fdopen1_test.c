#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char *name = "/data.dat";
  char *path = dirname(argv[0]);
  char *file_path = malloc(strlen(name) + strlen(path));
  strcpy(file_path, path);
  strcat(file_path, name);
  // 创建文件并返回文件描述符
  int fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC);
  if (fd == -1) {
    fputs("file open error", stdout);
    return -1;
  }
  fp = fdopen(fd, "w"); // 返回 写 模式的 FILE 指针
  fputs("NetWork C programming \n", fp);
  free(file_path);
  fclose(fp);
  return 0;
}
