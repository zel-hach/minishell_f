/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_quots.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:32:19 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/25 17:35:06 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*creat_s_quote_token(t_token *token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = S_QUOTE;
	new->next = NULL;
	new->prev = NULL;
	new->data = ft_strdup("");
	token = token->next;
	while (token && token->type != S_QUOTE)
	{
		new->data = join_quotes_data(&new->data, token->data);
		token = token->next;
	}
	return (new);
}
