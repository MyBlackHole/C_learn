#include <stdio.h>

int main(int argc, char **argv, char **env) {
  while (env && *env) {
    printf("%s\n", *env);
    ++env;
  }
}
