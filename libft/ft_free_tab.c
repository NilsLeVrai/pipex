/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:59:17 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/21 16:59:26 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab && tab[i])
	{
		while (tab[i] != NULL)
		{
			if (tab[i])
				free (tab[i]);
			i++;
		}
		if (tab)
			free (tab);
	}
}
