/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:24:29 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/18 12:11:13 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memset(void *ptr, int val, size_t count)
{
	size_t	i;
	char	*p;

	p = (char *)ptr;
	i = 0;
	while (i != count)
	{
		p[i] = (unsigned char)val;
		i++;
	}
	return (ptr);
}
