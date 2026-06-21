#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Answer 8:
  The first child writes a message to the pipe and the second child reads the message from the pipe and writes it to the terminal.
  The parent waits for the children to finish and prints a message for each child that is reaped.
 */

int main() {
  int fd[2];
  if (pipe(fd) < 0) {
    fprintf(stderr, "pipe failed\n");
    exit(1);
  }

  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }

  if (rc == 0) {
    printf("hello, I am first child (pid:%d)\n", (int)getpid());
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);

    char message[] = "from first child to second child";
    write(STDOUT_FILENO, message, sizeof(message));
    exit(0);
  }

  int rc2 = fork();

  if (rc2 < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }

  if (rc2 == 0) {
    printf("hello, I am second child (pid:%d)\n", (int)getpid());
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);

    char buffer[5];
    while (read(STDIN_FILENO, buffer, 5) > 0) {
      write(STDOUT_FILENO, buffer, 5);
    }
    write(STDOUT_FILENO, "\n", 1);

    exit(0);
  }

  close(fd[0]);
  close(fd[1]);

  int wc;
  while ((wc = wait(NULL)) > 0) {
    printf("parent (pid:%d) reaped child %d\n", (int)getpid(), wc);
  }
  return 0;
}