/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:21:48 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/19 02:03:54 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/pipex.h"

int main(int argc, char **argv)
{
	int		fd[2];
	int		pid;
	int		status;
	int		infile;
	int		outfile;
	char	**cmd1;
	char	**cmd2;

	if (argc != 5)
		error_args();
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		error_open();
	if (pipe(fd) < 0)
		error_pipe();
	pid = fork();
	if (pid < 0)
		error_fork();
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(infile);
		close(outfile);
		execve(cmd1[0], cmd1, NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
		pid = fork();
		if (pid < 0)
			error_fork();
		if (pid == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			dup2(outfile, STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			close(infile);
			close(outfile);
			execve(cmd2[0], cmd2, NULL);
		}
		else
		{
			waitpid(pid, &status, 0);
			close(fd[0]);
			close(fd[1]);
			close(infile);
			close(outfile);
		}
	}
	return (0);
}
