#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Answer 5 (wait):
 * Creates two child processes with two fork() calls (only the original parent
 * reaches the second fork; the first child exits before that). Each child sleeps
 * briefly and exits. The parent reaps every terminated child by calling wait()
 * in a loop until no children remain (wait returns -1 with ECHILD). Each
 * successful wait() returns the PID of one exited child and removes its zombie
 * entry from the process table.
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

  int wc;
  while ((wc = wait(NULL)) > 0) {
    printf("parent (pid:%d) reaped child %d\n", (int)getpid(), wc);
  }

  return 0;
}
