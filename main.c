/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:28:00 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/29 23:47:03 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_list
{
	int	infile;
	int	outfile;
	int	pipefd[2];
}		t_list;

void	error_message(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	first_child_process(t_list fd, char *cmd1)
{
	if (dup2(fd.infile, STDIN_FILENO) == -1)
		error_message("dup2 infile");
	if (dup2(fd.pipefd[1], STDOUT_FILENO) == -1)
		error_message("dup2 pipefd[1]");
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	close(fd.infile);
	execlp("/bin/sh", "sh", "-c", cmd1, NULL);
	error_message("execlp cmd1");
}

void	second_child_process(t_list fd, char *cmd2)
{
	if (dup2(fd.pipefd[0], STDIN_FILENO) == -1)
		error_message("dup2 pipefd[0]");
	if (dup2(fd.outfile, STDOUT_FILENO) == -1)
		error_message("dup2 outfile");
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	close(fd.outfile);
	execlp("/bin/sh", "sh", "-c", cmd2, NULL);
	error_message("execlp cmd2");
}

void	parent_process(t_list fd, pid_t pid1, pid_t pid2)
{
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	close(fd.infile);
	close(fd.outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv)
{
	t_list	fd;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		error_message("Wrong numbre of arguments.");
	fd.infile = open(argv[1], O_RDONLY);
	fd.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd.infile < 0 || fd.outfile < 0)
		error_message("Error on opening a file.");
	if (pipe(fd.pipefd) == -1)
		error_message("Pipe error.");
	pid1 = fork();
	if (pid1 < 0)
		error_message("Fork error on pid1.");
	if (pid1 == 0)
		first_child_process(fd, argv[2]);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			error_message("Fork error on pid2.");
		if (pid2 == 0)
			second_child_process(fd, argv[3]);
		else
			parent_process(fd, pid1, pid2);
	}
}
