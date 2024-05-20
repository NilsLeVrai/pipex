/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:27:11 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/18 15:19:38 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/pipex.h"

void error_open(void)
{
	perror("Error: Open failed");
	exit(EXIT_FAILURE);
}

void error_fork(void)
{
	perror("Error: Fork failed");
	exit(EXIT_FAILURE);
}

void error_pipe(void)
{
	perror("Error: Pipe failed");
	exit(EXIT_FAILURE);
}

void error_args()
{
	perror("Error: Wrong number of arguments\n");
	exit(EXIT_FAILURE);
}

void check_errors()
{
	error_args();
	error_pipe();
	error_fork();
}