#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Answer 4 (execvp):
 * Creates a pipe, forks, and runs ./4_echo in the child with execvp. Before exec,
 * the child redirects stdout to the pipe write end (dup2), so 4_echo output goes
 * into the pipe instead of the terminal. exec replaces the child's code but keeps
 * open file descriptors, so the redirect still applies after exec.
 * The parent closes the pipe write end, reads bytes from the read end, prints them
 * to its own stdout, and wait()s for the child. argv is forwarded unchanged so
 * 4_echo receives the same command-line arguments as this program (argv[0] is this
 * program's name; 4_echo skips it when printing args starting at i = 1).
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
    execvp("./4_echo", argv);
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