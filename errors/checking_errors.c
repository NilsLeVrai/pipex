/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:27:11 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/24 17:21:13 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void error_dup2()
{
	perror("Error: Dup2 failed");
	exit(EXIT_FAILURE);
}

void error_open()
{
	perror("Error: Open failed");
	exit(EXIT_FAILURE);
}

void error_fork()
{
	perror("Error: Fork failed");
	exit(EXIT_FAILURE);
}

void error_pipe()
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
	error_open();
	error_dup2();
}