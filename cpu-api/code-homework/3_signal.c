#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** Answer 3:
 * The child process will print "hello" and send a SIGCONT signal to the parent process.
 * The parent process will stop until the child sends a SIGCONT signal.
 * The parent process will print "goodbye".
*/

int main(void) {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    /* child */
    printf("hello\n");
    kill(getppid(), SIGCONT);
    exit(0);
  } else {
    /* parent: stop until child sends SIGCONT */
    kill(getpid(), SIGSTOP);
    printf("goodbye\n");
  }
  return 0;
}