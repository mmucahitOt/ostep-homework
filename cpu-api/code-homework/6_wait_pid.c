#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Answer 6 (waitpid):
 * Same fork layout as 5_wait.c: two children, one from each fork() in the
 * original parent. Instead of wait(NULL), the parent calls waitpid(rc, NULL, 0)
 * to block until the child whose PID is stored in rc (the first fork) exits.
 * waitpid with a specific PID waits only for that child, not the second one
 * (rc2); the second child must be reaped separately or it remains a zombie
 * until the parent exits.
 */

int main() {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("hello, I am child (pid:%d)\n", (int)getpid());
    printf("I am sleeping for 1 second (%d)\n", (int)getpid());
    sleep(1);
    printf("I am awake (%d)\n", (int)getpid());
    printf("I am exiting (%d)\n", (int)getpid());
    exit(0);
  }

  int rc2 = fork();
  if (rc2 < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc2 == 0) {
    printf("hello, I am child (pid:%d)\n", (int)getpid());
    printf("I am sleeping for 1 second (%d)\n", (int)getpid());
    sleep(1);
    printf("I am awake (%d)\n", (int)getpid());
    printf("I am exiting (%d)\n", (int)getpid());
    exit(0);
  }

  int wc = waitpid(rc, NULL, 0);
  if (wc < 0) {
    perror("waitpid failed");
    exit(1);
  }
  printf("parent (pid:%d) reaped first child %d\n", (int)getpid(), wc);

  wc = waitpid(rc2, NULL, 0);
  if (wc < 0) {
    perror("waitpid failed");
    exit(1);
  }
  printf("parent (pid:%d) reaped second child %d\n", (int)getpid(), wc);

  return 0;
}
