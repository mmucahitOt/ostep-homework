#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Answer 2:
 * The child process will write "hello, I am child" to the file, while the parent process will write "hello, I am parent" to the file.
 * This is because the child process will have its own copy of the file descriptor, while the parent process will have a copy of the file descriptor that is shared with the child process.
 * The child process will close the file descriptor after writing to it, while the parent process will close the file descriptor after waiting for the child process to finish.
 */

int main() {
  int file_descriptor =
      open("2.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
  if (file_descriptor < 0) {
    fprintf(stderr, "open failed\n");
    exit(1);
  }
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("hello, I am child (pid:%d)\n", (int)getpid());
    char *message = "hello, I am child\n";
    write(file_descriptor, message, strlen(message));
    close(file_descriptor);
  } else {
    printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
    char *message = "hello, I am parent\n";
    write(file_descriptor, message, strlen(message));
    close(file_descriptor);
    wait(NULL);
  }
  return 0;
}