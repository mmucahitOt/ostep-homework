#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 *  For Answer 4:
 *  Mimic the behavior of the echo command.
 */

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    printf("%s ", argv[i]);
  }
  printf("\n");
  return 0;
}