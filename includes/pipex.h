/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:55:50 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/05 16:04:28 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int	infile;
	int	outfile;
	int	pipefd[2];
}		t_pipex;

char	*find_path(char *cmd, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	error_message(const char *message);
void	first_child_process(t_pipex fd, char *cmd1, char **envp);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_execlp(char *cmd, char **envp);
void	parent_process(t_pipex fd, pid_t *pid);
void	second_child_process(t_pipex fd, char *cmd2, char **envp);

#endif
