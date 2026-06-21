#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Answer 4 (execl):
 * Same pipe, fork, dup2, and parent read/wait pattern as 4_execvp.c. The
 * difference is exec: execl lists arguments individually instead of passing an
 * argv array. Because execl is variadic, only a fixed argument list can be
 * passed at compile time; here argv[1] is forwarded manually as the single user
 * argument to 4_echo. The first execl parameter is the path to the executable;
 * the second is argv[0] for the new program (the program name).
 */

int main(int argc, char *argv[]) {
  int fd[2];
  int pipe_status = pipe(fd);
  if (pipe_status < 0) {
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
    execl("./4_echo", "./4_echo", argv[1], NULL);
  } else {
    close(fd[1]);
    char buffer[100];
    while (read(fd[0], buffer, 100) > 0) {
      printf("%s", buffer);
    }
    close(fd[0]);
    wait(NULL);
  }
  return 0;
}