/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:55:28 by hcabel            #+#    #+#             */
/*   Updated: 2019/04/23 13:23:05 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#define SEP '0'
#define WORD '1'

static char const	*skip(char mode, char const *s, char c)
{
	if (mode == SEP)
	{
		while (*s && *s == c)
			++s;
		return (s);
	}
	else
	{
		while (*s && *s != c)
			++s;
		return (s);
	}
}

static unsigned int	nbr_words(char const *s, char c)
{
	unsigned int words;

	words = 0;
	while (*s)
	{
		if (*s != c)
			++words;
		s = skip(WORD, s, c);
		s = skip(SEP, s, c);
	}
	return (words);
}

static char const	*fill_tab(char *str, char const *s, char c)
{
	unsigned int i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		++i;
	}
	return (s + i);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**tab;
	unsigned int	words;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	words = nbr_words(s, c);
	if ((tab = (char**)malloc(sizeof(char*) * (words + 1))) == NULL)
		return (NULL);
	i = 0;
	s = skip(SEP, s, c);
	while (i < words)
	{
		if ((tab[i] = ft_strnew(skip(WORD, s, c) - s)) == NULL)
		{
			while (i-- > 0)
				ft_strdel(tab + i);
			free(tab);
			return (NULL);
		}
		s = fill_tab(tab[i++], s, c);
		s = skip(SEP, s, c);
	}
	tab[i] = NULL;
	return (tab);
}
