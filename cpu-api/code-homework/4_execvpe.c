#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Answer 4 (execvpe):
 * Same pipe, fork, dup2, and parent read/wait pattern as 4_execvp.c. Uses
 * execvpe with a custom environment (e): the child receives only the variables
 * in envp, not the full parent environment. argv is forwarded unchanged. The
 * path "./4_echo" is used so the local binary is found directly; if the file
 * argument has no '/', execvpe would also search PATH (the p variant).
 */

int main(int argc, char *argv[]) {
  int fd[2];
  if (pipe(fd) < 0) {
    fprintf(stderr, "pipe failed\n");
    exit(1);
  }

  char *envp[] = {"OSTEP=homework", NULL};

  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execvpe("./4_echo", argv, envp);
    perror("execvpe failed");
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
