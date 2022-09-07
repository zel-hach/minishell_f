/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:47:29 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/22 10:53:47 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_lenght(int n)
{
	int	c;

	c = 0;
	if (n <= 0)
		c = 1;
	while (n != 0)
	{
		c++;
		n = n / 10;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int			j;
	char		*ptr;
	long int	i;

	i = n;
	j = ft_lenght(i);
	ptr = malloc(sizeof(char) * j + 1);
	if (!ptr)
		return (NULL);
	ptr[j--] = '\0';
	if (i < 0)
	{
		i = i * (-1);
		ptr[0] = '-';
	}
	if (i == 0)
	{
		ptr[0] = '0';
	}
	while (i > 0)
	{
		ptr[j--] = 48 + (i % 10);
		i = i / 10;
	}
	return (ptr);
}
