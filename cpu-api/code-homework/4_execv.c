#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Answer 4 (execv):
 * Same pipe, fork, dup2, and parent read/wait pattern as 4_execvp.c. Uses execv
 * with an explicit path to ./4_echo and forwards argv unchanged (like execvp
 * but without PATH search). The child inherits the parent's environment.
 */

int main(int argc, char *argv[]) {
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
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execv("./4_echo", argv);
    perror("execv failed");
    exit(1);
  } else {
    close(fd[1]);
    char buffer[100];
    ssize_t n;
    while ((n = read(fd[0], buffer, sizeof(buffer))) > 0) {
      write(STDOUT_FILENO, buffer, n);
    }
    close(fd[0]);
    wait(NULL);
  }
  return 0;
}
