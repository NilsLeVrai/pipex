/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:28:00 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/04 22:48:54 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes ./pipex infile cmd1 cmd2 outfile

void	error_message(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE); // free tout ce qu'il y'a dans les enfants (split, join, malloc, etc)
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
	ft_execlp(cmd1, NULL);
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
	ft_execlp(cmd2, NULL);
	error_message("execlp cmd2");
}

void	parent_process(t_list fd, pid_t *pid)
{
	int	i;

	i = 0;
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	close(fd.infile);
	close(fd.outfile);
	while (pid[i])
		waitpid(pid[i++], NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	fd;
	pid_t	pid[2];
	(void)envp;

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
		first_child_process(fd, argv[2]);
	else
	{
		pid[1] = fork();
		if (pid[1] < 0)
			error_message("Fork error on pid2.");
		if (pid[1] == 0)
			second_child_process(fd, argv[3]);
		else
			parent_process(fd, pid);
	}
}
