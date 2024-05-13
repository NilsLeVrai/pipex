/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:55:50 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/13 17:05:33 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>

//////////////////////////////////////////
////    ___ _ __ _ __ ___  _ __ ___   ////
////   / _ \ '__| '__/ _ \| '__/ __|  ////
////  |  __/ |  | | | (_) | |  \__ \  ////
////   \___|_|  |_|  \___/|_|  |___/  ////
//////////////////////////////////////////

void error_args(int argc, char **argv);
void error_pipe(void);
void error_fork(void);

//////////////////////////////
//       _                  //
// _ __ (_)_ __   _____  __ //
//| '_ \| | '_ \ / _ \ \/ / //
//| |_) | | |_) |  __/>  <  //
//| .__/|_| .__/ \___/_/\_\ //
//|_|     |_|               //
//////////////////////////////



///////////////////////////////
////         _   _ _       ////
////        | | (_) |      ////
////   _   _| |_ _| |___   ////
////  | | | | __| | / __|  ////
////  | |_| | |_| | \__ \  ////
////   \__,_|\__|_|_|___/  ////
///////////////////////////////

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
