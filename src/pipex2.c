/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:27:38 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/04 18:54:08 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void ft_execlp(char *cmd, char **envp)
{
	if (execve(cmd, (char *const *)cmd, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
