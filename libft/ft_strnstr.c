/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:09:24 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/25 14:40:37 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t size)
{
	char	*str1;
	char	*str2;
	size_t	i;
	size_t	j;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	j = 0;
	if (*str2 == '\0')
		return (str1);
	while (str1[i] != '\0' && i <= size)
	{
		while (str1[i + j] == str2[j] && i + j < size)
		{
			if (str2[j + 1] == '\0')
			{
				return (str1 + i);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
