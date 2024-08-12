/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:15:59 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/12 15:58:36 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	args_unsigned(va_list args)
{
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	return (ft_putnbr_base(nbr, "0123456789"));
}
