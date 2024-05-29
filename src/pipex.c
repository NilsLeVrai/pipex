/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:21:48 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/29 18:00:40 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
parent fd[1] --> pipe --> child fd[0] --> child fd[1] --> pipe --> parent fd[0] 
    write                    read       	write                     read
*/


static void child_process(char **argv, int *fd, char **env)
{
	int infile;

	infile = open(argv[1], O_RDONLY);
	dup2(infile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(infile);
	ft_execve(argv[2], env);
}

static void parent_process(char **argv, int *fd, char **env)
{
	int outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fd[0], 0);
	dup2(outfile, 1);
	close(fd[0]);
	close(outfile);
	ft_execve(argv[3], env);
}

int main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		pid;

	if (argc != 5)
		error_args();
	if (pipe(fd) < 0)
		error_pipe();
	pid = fork();
	if (pid < 0)
		error_fork();
	if (pid == 0)
		child_process(argv, fd, env);
	waitpid(pid, NULL, 0);	
	parent_process(argv, fd, env);
	return (0);
}
