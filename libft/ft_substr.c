/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:49:48 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/25 12:40:18 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	str = (char *)s;
	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		return (ft_strdup(""));
	if (ft_strlen(str) - start < len)
		len = ft_strlen(str) - start;
	p = malloc(len + 1 * sizeof(char));
	if (!p)
		return (NULL);
	while (str[i] != '\0')
	{
		if (i >= start && j < len)
			p[j++] = str[i];
		i++;
	}
	p[j] = '\0';
	return (p);
}
