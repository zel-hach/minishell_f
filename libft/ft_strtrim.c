/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:33:57 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/21 13:30:39 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_cherche(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		a;
	int		b;
	int		i;
	char	*ptr;

	a = 0;
	if (!s1)
		return (NULL);
	while (s1[a] != '\0' && ft_cherche(s1[a], set))
		a++;
	b = ft_strlen(s1);
	while (b > a && ft_cherche(s1[b - 1], set))
		b--;
	ptr = malloc(sizeof(s1) * (b - a + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (a < b)
	{
		ptr[i++] = s1[a++];
	}
	ptr[i] = '\0';
	return (ptr);
}
