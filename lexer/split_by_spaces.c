/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:16:41 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/22 22:55:35 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char s)
{
	if (s == '\t' || s == '\n' || s == '\v'
		|| s == '\f' || s == '\r' || s == ' ')
		return (1);
	return (0);
}

static int	ft_countword(const char *s)
{
	int		word;
	int		i;
	char	*str;

	str = (char *)s;
	word = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (str[i] != '\0')
			word++;
		while (str[i] && !is_space(str[i]))
			i++;
	}
	return (word);
}

static char	**ft_filltab(char **tab, const char *s)
{
	int	i;
	int	j;
	int	k;
	int	word;

	word = ft_countword(s);
	k = 0;
	i = 0;
	while (k < word)
	{
		while (s[i] && is_space(s[i]))
			i++;
		j = 0;
		while (s[i] && !is_space(s[i]))
			tab[k][j++] = s[i++];
		tab[k][j] = '\0';
		k++;
	}
	tab[k] = NULL;
	return (tab);
}

static char	**ft_taballoc(char **tab, int j, int k)
{
	int	i;

	i = 0;
	tab[k] = (char *)malloc(sizeof(char) * (j + 1));
	if (!tab[k])
	{
		while (i < k)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		return (NULL);
	}
	return (tab);
}

char	**split_whitespaces(char *s)
{
	char	**tab;
	int		i;
	int		j;
	int		word;

	if (!s)
		return (NULL);
	word = ft_countword(s);
	tab = (char **)malloc(sizeof(char *) * (word + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (word > 0)
	{
		while (s[i] && is_space(s[i]))
			i++;
		j = 0;
		while (s[i] && !is_space(s[i++]))
			j++;
		if (!ft_taballoc(tab, j, ft_countword(s) - word))
			return (NULL);
		word--;
	}
	tab = ft_filltab(tab, s);
	return (free(s), tab);
}
