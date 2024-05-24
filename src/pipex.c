/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:21:48 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/24 17:59:47 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
parent fd[1] --> pipe --> child fd[0] --> child fd[1] --> pipe --> parent fd[0] 
    write                    read       	write                     read
*/

/* 
static void child_process(char **argv, int *fd, char **env)
{
	int infile;

	infile = open(argv[1], O_RDONLY); path, flag, mode
	dup2 pour rediriger les fd??
	"oublie pas de close" -achatzit 2024
	execve pour executer les commandes 
	
}

static void parent_process(char **argv, int *fd, char **env)
{
	int outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777); path, flag, mode
	dup2 pour rediriger les fd??
	"oublie pas de close" -achatzit 2024
	execve pour executer les commandes (path, argv, envp) ex: (/usr/bin/, "ls -l", envp)
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

	if (argc != 5)
		error_args();
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