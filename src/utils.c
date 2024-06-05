/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:28 by niabraha          #+#    #+#             */
/*   Updated: 2024/06/05 15:58:19 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*char1;
	unsigned char	*char2;

	char1 = (unsigned char *) s1;
	char2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	i = 0;
	while (n - 1 > i && char1[i] == char2[i])
	{
		if (char1[i] != char2[i])
			return (char1[i] - char2[i]);
		else if (char1[i] == '\0' || char2[i] == '\0')
			return (char1[i] - char2[i]);
		i++;
	}
	return (char1[i] - char2[i]);
}

static void	*free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

static char	*fill_tab(const char *tab, char c)
{
	char	*word;
	size_t	len;

	len = 0;
	while (tab[len] && tab[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (len--)
		word[len] = tab[len];
	return (word);
}

static int	count_words(char const *s, char c)
{
	size_t	words;
	int		is_del;

	words = 0;
	is_del = 0;
	while (*s)
	{
		if (*s != c && is_del == 0)
		{
			is_del = 1;
			words++;
		}
		else if (*s == c)
			is_del = 0;
		s++;
	}
	return (words);
}

char	**ft_split(const char *s, char c)
{
	char	**p;
	int		i;
	int		nb_words;
	size_t	len_sub;

	nb_words = count_words(s, c);
	p = (char **)ft_calloc((nb_words + 1), sizeof(char *));
	if (!p || !s)
		return (NULL);
	i = -1;
	while (nb_words > ++i)
	{
		len_sub = 0;
		while (*s == c && *s)
			s++;
		while (s[len_sub] != c && s[len_sub])
			len_sub++;
		p[i] = fill_tab(s, c);
		if (!p[i])
			return (free_tab(p));
		s += len_sub;
	}
	p[i] = NULL;
	return (p);
}
