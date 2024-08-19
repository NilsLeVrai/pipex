/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:28:00 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/19 22:22:54 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	first_child_process(t_pipex fd, char *cmd1, char **envp)
{
	if (dup2(fd.pipefd[1], STDOUT_FILENO) == -1)
		error_message("dup2 pipefd[1]");
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	ft_execlp(cmd1, envp);
}

static void	second_child_process(t_pipex fd, char *cmd2, char **envp)
{
	if (dup2(fd.pipefd[0], STDIN_FILENO) == -1)
		error_message("dup2 pipefd[0]");
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	ft_execlp(cmd2, envp);
}

static void	parent_process(t_pipex *fd)
{
	close(fd->pipefd[0]);
	close(fd->pipefd[1]);
	waitpid(fd->pid[0], &(fd->status), 0);// le goat
	waitpid(fd->pid[1], &(fd->status), 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	fd;

	if (argc != 3)
		return (ft_printf("Wrong number of arguments\n"));
	if (pipe(fd.pipefd) == -1)
		return (error_message("Pipe error"), -1);
	fd.pid[0] = fork();
	if (fd.pid[0] < 0)
		return (error_message("Fork error on pid[0]"), -1);
	if (fd.pid[0] == 0)
		first_child_process(fd, argv[1], envp);
	else
	{
		fd.pid[1] = fork();
		if (fd.pid[1] < 0)
			return (error_message("Fork error on pid[1]"), -1);
		if (fd.pid[1] == 0)
			second_child_process(fd, argv[2], envp);
		else
			parent_process(&fd);
	}
	if (WIFEXITED(fd.status))
		return (WEXITSTATUS(fd.status));
	return (0);
}
