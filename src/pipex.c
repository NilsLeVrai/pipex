/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:28:00 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/05 15:59:34 by niabraha         ###   ########.fr       */
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
	if (dup2(fd.pipefd[0], STDIN_FILENO) == -1)
		error_message("dup2 pipefd[0]");
	if (dup2(fd.outfile, STDOUT_FILENO) == -1)
		error_message("dup2 outfile");
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	close(fd.outfile);
	ft_execlp(cmd2, envp);
	error_message("execlp cmd2");
}

void	parent_process(t_pipex fd, pid_t *pid)
{
	int	i;

	i = 0;
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	waitpid(pid[i], NULL, 0);
	waitpid(pid[i + 1], NULL, 0);
	close(fd.infile);
	close(fd.outfile);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	fd;
	pid_t	pid[2];

	if (argc != 5)
		error_message("Wrong number of arguments.");
	fd.infile = open(argv[1], O_RDONLY);
	fd.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd.infile < 0 || fd.outfile < 0)
		error_message("Error on opening a file.");
	if (pipe(fd.pipefd) == -1)
		error_message("Pipe error.");
	pid[0] = fork();
	if (pid[0] < 0)
		error_message("Fork error on pid1.");
	if (pid[0] == 0)
		first_child_process(fd, argv[2], envp);
	else
	{
		pid[1] = fork();
		if (pid[1] < 0)
			error_message("Fork error on pid2.");
		if (pid[1] == 0)
			second_child_process(fd, argv[3], envp);
		else
			parent_process(fd, pid);
	}
}
