/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_dollar_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:52:50 by ael-idri          #+#    #+#             */
/*   Updated: 2022/09/05 17:09:46 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*space_token(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->type = SPACE;
	new->data = ft_strdup(" ");
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*empty_token(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->type = WORD;
	new->data = ft_strdup("");
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	creat_dollar_token(t_token **head, char *data, t_token *tok, t_env *env)
{
	t_token	*new;
	t_token	*space;

	space = space_token();
	new = (t_token *)malloc(sizeof(t_token));
	if (!new || !space)
		return (0);
	new->type = WORD;
	if (data[0] != '$')
		new->data = ft_strdup(data);
	else
		new->data = dollar_v(data, tok, env);
	new->next = NULL;
	new->prev = NULL;
	add_back_token(head, &new);
	add_back_token(head, &space);
	return (1);
}

void	elimine__dollar(t_token **head, t_token **token, t_token **tem)
{
	if ((*tem)->prev)
		(*tem)->prev->next = (*tem)->next->next;
	else
		*head = (*tem)->next->next;
	if ((*tem)->next->next)
		(*tem)->next->next->prev = (*tem)->prev;
	*token = (*tem)->next->next;
	(*tem)->next->next = NULL;
	free_tokens(tem);
}

void	add_token_to_main_token(t_token **head, t_token **token,
	t_token **new, t_token **tem)
{
	t_token	*last;

	if (!(*new))
	{
		elimine__dollar(head, token, tem);
		return ;
	}
	if ((*tem)->prev)
		(*tem)->prev->next = *new;
	else
		*head = *new;
	last = last_token(*new);
	(*new)->prev = (*tem)->prev;
	(*tem)->prev = NULL;
	if ((*tem)->next->next)
		(*tem)->next->next->prev = last;
	last->next = (*tem)->next->next;
	(*tem)->next->next = NULL;
	free_tokens(tem);
	*token = last;
}
