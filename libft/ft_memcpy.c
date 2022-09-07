/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:41:11 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/25 18:30:09 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*dest1;
	char			*src1;

	dest1 = (char *)dest;
	src1 = (char *)src;
	i = 0;
	if (dest1 == NULL && src1 == NULL)
	{
		return (NULL);
	}
	while (n)
	{
		*dest1 = *src1;
		dest1++;
		src1++;
		n--;
	}
	return (dest);
}
