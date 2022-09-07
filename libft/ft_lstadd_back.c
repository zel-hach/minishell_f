/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:19:49 by zel-hach          #+#    #+#             */
/*   Updated: 2021/11/26 15:38:09 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*ptr;

	ptr = *alst;
	if (alst)
	{
		if (*alst == NULL)
		{
			*alst = new;
		}
		else
		{
			while (ptr -> next != NULL)
			{
				ptr = ptr -> next;
			}
			ptr -> next = new;
		}
	}
}
