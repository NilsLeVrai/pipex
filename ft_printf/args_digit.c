/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_digit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:21:55 by niabraha          #+#    #+#             */
/*   Updated: 2024/05/22 16:21:17 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	args_digit(va_list args)
{
	long	nbr;
	int		is_neg;

	nbr = va_arg(args, int);
	is_neg = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		is_neg++;
		if (ft_putchar_fd_safe('-', 1) == -1)
			return (-1);
	}
	return (ft_putnbr_base(nbr, "0123456789") + is_neg);
}
