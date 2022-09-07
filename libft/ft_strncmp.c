/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:32:44 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/24 20:19:53 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t length)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	i = 0;
	if (length == 0)
	{
		return (0);
	}
	while (t1[i] && t2[i] && t1[i] == t2[i] && i < length - 1)
	{
		i++;
	}
	return (t1[i] - t2[i]);
}
