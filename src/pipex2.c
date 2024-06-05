/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:27:38 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/05 18:53:19 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* static char	*return_path(char *possi)
{
	possible_path = ft_strjoin(all_paths[i], "/");
	final_path = ft_strjoin(possible_path, cmd);
	free(possible_path);
	if (access(final_path, F_OK) == 0)
		return (final_path);
	free(final_path);
	i++;
} */

char	*find_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	*final_path;
	char	*possible_path;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		possible_path = ft_strjoin(all_paths[i], "/");
		final_path = ft_strjoin(possible_path, cmd);
		free(possible_path);
		if (access(final_path, F_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
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
		error_message("error splitting the command.");
	path = find_path(tab[0], envp);
	if (!path)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
		error_message("Command not found");
		exit(EXIT_FAILURE);
	}
	if (access(path, F_OK) == -1)
		error_message("");
	if (execve(path, tab, envp) == -1)
		error_message("Permission denied");
}
