/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:28:00 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/18 19:02:47 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child_process(t_pipex fd, char *cmd1, char **envp, char **argv)
{
	fd.infile = open(argv[1], O_RDONLY);
	if (fd.infile < 0)
	{
		close(fd.pipefd[0]);
		close(fd.pipefd[1]);
		error_message(argv[1]);
	}
	if (dup2(fd.infile, STDIN_FILENO) == -1)
		error_message("dup2 infile");
	if (dup2(fd.pipefd[1], STDOUT_FILENO) == -1)
		error_message("dup2 pipefd[1]");
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	close(fd.infile);
	ft_execlp(cmd1, envp);
}

void	second_child_process(t_pipex fd, char *cmd2, char **envp, char **argv)
{
	fd.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd.outfile < 0)
	{
		close(fd.pipefd[0]);
		close(fd.pipefd[1]);
		error_message(argv[4]);
	}
	if (dup2(fd.outfile, STDOUT_FILENO) == -1)
		error_message("dup2 outfile");
	if (dup2(fd.pipefd[0], STDIN_FILENO) == -1)
		error_message("dup2 pipefd[0]");
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	close(fd.outfile);
	ft_execlp(cmd2, envp);
}

void	parent_process(t_pipex *fd, pid_t *pid)
{
	close(fd->pipefd[0]);
	close(fd->pipefd[1]);
	waitpid(pid[0], &(fd->status), 0);
	waitpid(pid[1], &(fd->status), 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	fd;

	if (argc != 5)
		return (ft_printf("Wrong number of arguments\n"));
	if (pipe(fd.pipefd) == -1)
		return (error_message("Pipe error"), -1);
	fd.pid[0] = fork();
	if (fd.pid[0] < 0)
		return (error_message("Fork error on pid[0]"), -1);
	if (fd.pid[0] == 0)
		first_child_process(fd, argv[2], envp, argv);
	else
	{
		fd.pid[1] = fork();
		if (fd.pid[1] < 0)
			return (error_message("Fork error on pid[1]"), -1);
		if (fd.pid[1] == 0)
			second_child_process(fd, argv[3], envp, argv);
		else
			parent_process(&fd, fd.pid);
	}
	if (WIFEXITED(fd.status))
		return (WEXITSTATUS(fd.status));
	return (0);
}
