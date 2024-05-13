/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:27:11 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/13 17:11:13 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/pipex.h"

void error_args(int argc, char **argv)
{
	if (argc != 5)
	{
		
	}
}

void check_errors(int argc, char **argv)
{
	error_args(argc, argv);
	error_pipe();
	error_fork();
}