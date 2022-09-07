/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:30:06 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/25 13:55:47 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (i >= size)
		return (size + j);
	if (!*src)
		return (i);
	k = 0;
	while (src[k] && (i + k < size - 1))
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[i + k] = '\0';
	return (j + i);
}
