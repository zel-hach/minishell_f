/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:34:07 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/20 21:34:29 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char	*p;
	size_t	i;

	i = 0;
	if (elementCount == 0)
		elementCount = 1;
	if (elementSize == 0)
		elementSize = 1;
	p = malloc (elementCount * elementSize);
	if (!p)
		return (NULL);
	else if (p)
	{
		ft_bzero(p, elementSize * elementCount);
	}
	return (p);
}
