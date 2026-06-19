#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Answer 1:
 * The child process will have a different value of x than the parent process.
 * This is because the child process will have its own copy of the variable x,
 * while the parent process will have a copy of the variable x that is shared
 * with the child process.
 */

int main() {
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("hello, I am child (pid:%d)\n", (int)getpid());
    printf("the address of x is %p\n", &x);
    printf("x: %d\n", x);

    printf("reassigning x to 0\n");
    x = 0;
    printf("x: %d\n", x);
  } else {
    printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
    printf("x: %d\n", x);
    printf("the address of x is %p\n", &x);
    printf("reassigning x to 1\n");
    x = 1;
    printf("x: %d\n", x);
  }
  return 0;
}