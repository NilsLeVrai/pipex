/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:28:00 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/07 23:14:23 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_message(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	first_child_process(t_pipex fd, char *cmd1, char **envp)
{
	if (dup2(fd.infile, STDIN_FILENO) == -1)
		error_message("dup2 infile");
	if (dup2(fd.pipefd[1], STDOUT_FILENO) == -1)
		error_message("dup2 pipefd[1]");
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	close(fd.infile);
	ft_execlp(cmd1, envp);
	error_message("execlp cmd1");
}

void	second_child_process(t_pipex fd, char *cmd2, char **envp)
{
	if (dup2(fd.outfile, STDOUT_FILENO) == -1)
		error_message("dup2 outfile");
	if (dup2(fd.pipefd[0], STDIN_FILENO) == -1)
		error_message("dup2 pipefd[0]");
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	close(fd.outfile);
	ft_execlp(cmd2, envp);
	error_message("execlp cmd2");
}

void	parent_process(t_pipex fd, pid_t *pid)
{
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	close(fd.infile);
	close(fd.outfile);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	fd;

	if (argc != 5)
		error_message("Wrong number of arguments.");
	fd.infile = open(argv[1], O_RDONLY);
	fd.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd.infile < 0 || fd.outfile < 0)
		error_message("No such file or directory");
	if (pipe(fd.pipefd) == -1)
		error_message("Pipe error.");
	fd.pid[0] = fork();
	if (fd.pid[0] < 0)
		error_message("Fork error on pid1.");
	if (fd.pid[0] == 0)
		first_child_process(fd, argv[2], envp);
	else
	{
		fd.pid[1] = fork();
		if (fd.pid[1] < 0)
			error_message("Fork error on pid2.");
		if (fd.pid[1] == 0)
			second_child_process(fd, argv[3], envp);
		else
			parent_process(fd, fd.pid);
	}
}
