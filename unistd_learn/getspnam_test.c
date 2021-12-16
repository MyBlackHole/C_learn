#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  char *crypted_pass;
  char *input_pass;
  struct spwd *shadow_line;
  if (argc < 2) {
    fprintf(stderr, "user \n");
    exit(1);
  }

  input_pass = getpass("PassWord:");

  shadow_line = getspnam(argv[1]);

  crypted_pass = crypt(input_pass, shadow_line->sp_pwdp);

  if (strcmp(shadow_line->sp_pwdp, crypted_pass) == 0) {
    puts("ok");
  } else {
    puts("faile");
  }

  exit(0);
}
