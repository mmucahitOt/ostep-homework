#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int fd[2];
  if (pipe(fd) < 0) {
    fprintf(stderr, "pipe failed\n");
    exit(1);
  }

  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    /* child */
    close(fd[0]);              /* close read end — child only writes */
    printf("hello\n");
    char c = 'x';
    write(fd[1], &c, 1);       /* notify parent */
    close(fd[1]);
    exit(0);
  } else {
    /* parent */
    close(fd[1]);              /* close write end — parent only reads */
    char c;
    read(fd[0], &c, 1);        /* block until child writes */
    printf("goodbye\n");
    close(fd[0]);
  }
  return 0;
}