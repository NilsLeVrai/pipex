/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:12:56 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/22 16:21:17 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	args_char(va_list args)
{
	char	c;

	c = va_arg(args, int);
	return (ft_putchar_fd_safe(c, 1));
}
