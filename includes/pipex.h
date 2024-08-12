/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:55:50 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/17 16:34:35 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		status;
	int		pipefd[2];
	pid_t	pid[2];
}		t_pipex;

char	*check_path(char *cmd, char *path);
char	*find_path(char *cmd, char **envp);
void	error_message(const char *message);
void	ft_execlp(char *cmd, char **envp);
void	raise_error(char *error, char *details, int error_code);

#endif
