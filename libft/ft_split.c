/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:00:40 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/24 14:11:54 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	lenght_string(char const *s1, char c)
{
	int	compt_mot;
	int	j;

	j = 0;
	compt_mot = 0;
	if (!s1)
		return (0);
	while (s1[j] != '\0')
	{
		if (s1[j] != c && (s1[j + 1] == c || s1[j + 1] == '\0'))
		{
			compt_mot ++;
		}
		j++;
	}
	return (compt_mot);
}

static int	lenght_char(char const *s2, char c, int i)
{
	int	len;

	len = 0;
	while (s2[i] != c && s2[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	**frre(char **dest, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)dest[j]);
	}
	free(dest);
	return (NULL);
}

static char	**afficher(char const *str, char **dest, char c, int d)
{
	int	a;
	int	b;
	int	k;

	a = 0;
	b = 0;
	while (str[a] != '\0' && b < d)
	{
		k = 0;
		while (str[a] == c)
			a++;
		dest[b] = malloc(sizeof(char) * lenght_char(str, c, a) + 1);
		if (dest[b] == NULL)
			return (frre(dest, b));
		while (str[a] != '\0' && str[a] != c)
		{
			dest[b][k] = str[a];
			k++;
			a++;
		}
		dest[b][k] = '\0';
		b++;
	}
	dest[b] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		l;

	if (!s)
		return (NULL);
	l = lenght_string(s, c);
	dest = malloc(sizeof(char *) * (l + 1));
	if (dest == NULL)
		return (NULL);
	return (afficher(s, dest, c, l));
}
