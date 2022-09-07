/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:21:17 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/24 14:33:19 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*ptr;

	list = *lst;
	while (list != NULL)
	{
		ptr = list -> next;
		del(list -> content);
		free (list);
		list = ptr;
	}
	*lst = NULL;
}
