/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:02:06 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/24 15:11:53 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(src);
	j = -1;
	if (i + 1 < size)
		while (++j <= i)
			dst[j] = src[j];
	else if (size)
	{
		while (++j < size - 1)
			dst[j] = src[j];
		dst[j] = 0;
	}
	return (i);
}
