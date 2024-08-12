/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:27:38 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/21 18:01:33 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	raise_error(char *error, char *details, int error_code)
{
	write(2, details, ft_strlen(details));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(error_code);
}

void	error_message(const char *message)
{
	perror(message);
	exit(errno);
}

char	*check_path(char *cmd, char *path)
{
	char	*possible_path;
	char	*final_path;

	possible_path = ft_strjoin(path, "/");
	final_path = ft_strjoin(possible_path, cmd);
	free(possible_path);
	if (access(final_path, F_OK) == 0)
		return (final_path);
	free(final_path);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	*final_path;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (all_paths[++i])
	{
		final_path = check_path(cmd, all_paths[i]);
		if (final_path)
			return (final_path);
	}
	i = -1;
	while (all_paths[++i])
		free(all_paths[i]);
	free(all_paths);
	return (NULL);
}

void	ft_execlp(char *cmd, char **envp)
{
	char	*path;
	char	**tab;
	int		i;

	i = -1;
	tab = ft_split(cmd, ' ');
	if (!tab)
		error_message("Error splitting the command");
	path = find_path(tab[0], envp);
	if (!path)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
		raise_error("command not found", cmd, 127);
		exit(EXIT_FAILURE);
	}
	if (execve(path, tab, envp) == -1)
	{
		free(tab);
		free(path);
		error_message("Permission denied");
	}
}
