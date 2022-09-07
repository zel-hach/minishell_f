/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:09:56 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/28 13:20:56 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	if (!str && !str[i])
		return (NULL);
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return (&str[i + 1]);
		else
			i++;
	}
	return (NULL);
}
