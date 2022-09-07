/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:55:36 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/18 22:23:38 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	join_tow_words(t_token **head, t_token **run)
{
	t_token	*new;
	t_token	*del;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	del = *run;
	new->type = WORD;
	new->data = ft_strjoin((*run)->data, (*run)->next->data);
	new->next = (*run)->next->next;
	new->prev = (*run)->prev;
	if ((*run)->prev)
		(*run)->prev->next = new;
	else
		*head = new;
	if ((*run)->next->next)
		(*run)->next->next->prev = new;
	(*run)->next->next = NULL;
	(*run) = new;
	free_tokens(&del);
	return (1);
}

int	join_words(t_token **token)
{
	t_token	*run;

	run = *token;
	while (run)
	{
		while (run && run->type != WORD)
			run = run->next;
		while (run && run->next && run->next->type == WORD)
			if (!join_tow_words(token, &run))
				return (0);
		if (run)
			run = run->next;
	}
	return (1);
}
