/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 06:32:43 by ael-idri          #+#    #+#             */
/*   Updated: 2022/09/05 18:13:55 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	elimine_dollar(t_token **head, t_token **token)
{
	t_token	*tem;

	tem = *token;
	tem->next->prev = tem->prev;
	if (tem->prev)
		tem->prev->next = tem->next;
	else
		*head = tem->next;
	*token = tem->next;
	tem->next = NULL;
	tem->prev = NULL;
	free_tokens(&tem);
}

void	add_back_token(t_token **head, t_token **new)
{
	t_token	*last;

	if (!(*head))
		*head = *new;
	else
	{
		last = last_token(*head);
		last->next = *new;
		(*new)->prev = last;
	}
}

int	replace_dollar_with_value_elem(t_token **head, t_token **token, t_env *env)
{
	t_token	*new;
	t_token	*tem;
	char	**data;
	int		i;

	i = 0;
	tem = *token;
	data = split_whitespaces(dollar_v((*token)->next->data, *token, env));
	if (!data)
		new = NULL;
	else
		new = empty_token();
	while (data && data[i])
	{
		if (!creat_dollar_token(&new, data[i], *token, env))
			return (0);
		i++;
	}
	free_tab(&data);
	add_token_to_main_token(head, token, &new, &tem);
	return (1);
}

void	chanche_quote_type(t_token **token)
{
	t_token	*run;

	run = *token;
	while (run)
	{
		if (run->type == D_QUOTE || run->type == S_QUOTE)
			run->type = WORD;
		run = run->next;
	}
}

int	change_dollars(t_token **token, t_env *env)
{
	t_token	*run;

	run = *token;
	while (run)
	{
		while (run && run->type != DOLLAR)
			run = run->next;
		if (run && run->next && (run->next->type == D_QUOTE
				|| run->next->type == S_QUOTE))
			elimine_dollar(token, &run);
		else if (run && run->next && run->next->type == WORD)
		{
			if (!replace_dollar_with_value_elem(token, &run, env))
				return (0);
		}
		else if (run)
		{
			run->type = WORD;
			run = run->next;
		}
	}
	chanche_quote_type(token);
	if (!join_words(token))
		return (0);
	return (1);
}
