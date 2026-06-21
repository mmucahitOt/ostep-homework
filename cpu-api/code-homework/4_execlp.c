#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Answer 4 (execlp):
 * Same pipe, fork, dup2, and parent read/wait pattern as the other Answer 4
 * programs. Uses execlp: arguments are listed individually (like execl), and if
 * the file name contains no '/', PATH is searched. Here "./4_echo" is used so
 * the binary in the current directory is run directly. argv[1] is forwarded
 * manually when present; execlp inherits the parent's environment.
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
    if (argc < 2) {
      execlp("./4_echo", "4_echo", NULL);
    } else {
      execlp("./4_echo", "4_echo", argv[1], NULL);
    }
    perror("execlp failed");
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
