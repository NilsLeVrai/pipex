#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == 0) {
        // This is the child process
        printf("Child process: PID = %d, Child PID = %d\n", getpid(), child_pid);
    } else {
        // This is the parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), child_pid);
	}
}
