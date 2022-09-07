/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:15:39 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/28 21:42:49 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem ;

	elem = malloc(sizeof(t_list));
	if (!elem)
	{
		return (NULL);
	}
	elem -> content = content;
	elem -> next = NULL;
	return (elem);
}
