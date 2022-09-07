/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 09:45:11 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/18 12:44:28 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*str;

	str = (char *)s;
	len = ft_strlen(str);
	if ((char)c == '\0')
		return (&str[len]);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return (&str[len]);
		len--;
	}
	return (0);
}
