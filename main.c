#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void error_and_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s infile \"cmd1\" \"cmd2\" outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int infile = open(argv[1], O_RDONLY);
    if (infile < 0) error_and_exit("open infile");

    int outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile < 0) error_and_exit("open outfile");

    int pipefd[2];
    if (pipe(pipefd) == -1) error_and_exit("pipe");

    pid_t pid1 = fork();
    if (pid1 < 0) error_and_exit("fork");

    if (pid1 == 0) {
        // First child process for "cmd1"
        if (dup2(infile, STDIN_FILENO) == -1) error_and_exit("dup2 infile");
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) error_and_exit("dup2 pipefd[1]");
        
        close(pipefd[0]);
        close(pipefd[1]);
        close(infile);
        close(outfile);
        
        execlp("/bin/sh", "sh", "-c", argv[2], NULL);
        error_and_exit("execlp cmd1");
    }

    pid_t pid2 = fork();
    if (pid2 < 0) error_and_exit("fork");

    if (pid2 == 0) {
        // Second child process for "cmd2"
        if (dup2(pipefd[0], STDIN_FILENO) == -1) error_and_exit("dup2 pipefd[0]");
        if (dup2(outfile, STDOUT_FILENO) == -1) error_and_exit("dup2 outfile");
        
        close(pipefd[0]);
        close(pipefd[1]);
        close(infile);
        close(outfile);
        
        execlp("/bin/sh", "sh", "-c", argv[3], NULL);
        error_and_exit("execlp cmd2");
    }

    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);
    close(infile);
    close(outfile);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
