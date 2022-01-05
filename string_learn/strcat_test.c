#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *firstName = "Theo";
  char *lastName = "Tsao";
  char *name = (char *)malloc(strlen(firstName) + strlen(lastName));
  strcpy(name, firstName);
  strcat(name, lastName);
  printf("%s\n", name);
  return 0;
}
