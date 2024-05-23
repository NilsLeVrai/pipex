/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:21:48 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/23 16:10:52 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
parent fd[1] --> pipe --> child fd[0] --> child fd[1] --> pipe --> parent fd[0] 
    write                    read       	write                     read
*/

/* static void execcommand(char *command, char **env)
{
	char	**argv;
	char	*path;
	int		i;

	i = 0;
	argv = ft_split(command, ' ');
	path = ft_strjoin("/bin/", argv[0]);
	execve(path, argv, env);
	free(path);
	free(argv);
}

static void child_process(char **argv, int *fd, char **env)
{
	int infile;

	infile = open(argv[1], O_RDONLY);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(infile);
	execcommand(argv[2], env);
	
}

static void parent_process(char **argv, int *fd, char **env)
{
	int outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	close(outfile);
	execve(argv[3], &argv[3], env);
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
} */

static int nb_path(char *path)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (path[i])
	{
		if (path[i] == ':')
			nb++;
		i++;
	}
	if (nb == 1 && path[i - 1] == '\0')
		return (1);
	return (nb + 1);
}

static char *find_path(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
            return (env[i] + 5);
        i++;
    }
    return (NULL);
}

int main(int argc, char **argv, char **env)
{
    (void) argc;
    (void) argv;
	char *path;
    char **tab;

	path = find_path(env);
	printf("\n\n%s\n", path);
	int nb = nb_path(path);
	printf("%d\n", nb);
    tab = ft_split(path, ':');
	while (*tab)
	{
		printf("%s\n", *tab);
		tab++;
	}
    return (0);
}