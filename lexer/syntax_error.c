/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:31:08 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/22 20:05:45 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prev_is_redirection(t_token *tok)
{
	if (!tok)
		return (0);
	tok = tok->prev;
	while (tok && tok->type == SPACE)
			tok = tok->prev;
	if (tok && (tok->type >= REDIREC_IN && tok->type <= APPEND))
		return (1);
	return (0);
}

int	pass_quote_word(t_token	**token)
{
	int	token_type;

	token_type = (*token)->type;
	*token = (*token)->next;
	while (*token && (*token)->type != token_type)
		*token = (*token)->next;
	if (!(*token))
		return (0);
	return (1);
}

int	check_redirec_word(t_token **head, t_token **token)
{
	*token = (*token)->next;
	while (*token && (*token)->type == SPACE)
		*token = (*token)->next;
	if (*token && ((*token)->type == WORD || (*token)->type == DOLLAR))
		return (1);
	if (*token && ((*token)->type == D_QUOTE || (*token)->type == S_QUOTE))
	{
		if (!pass_quote_word(token))
			return (manage_syntax_error(D_QUOTE, head));
		return (1);
	}
	return (0);
}

int	check_pipe(t_token *token)
{
	t_token	*go_left;

	go_left = token;
	if (go_left->prev)
		go_left = go_left->prev;
	else
		return (0);
	while (go_left && go_left->type == SPACE)
		go_left = go_left->prev;
	if (token->next)
		token = token->next;
	else
		return (0);
	while (token && token->type == SPACE)
		token = token->next;
	if (!go_left || go_left->type == PIPE || !token || token->type == PIPE)
		return (0);
	return (1);
}

int	syntax_error(t_token **tok, t_env *env)
{
	t_token	*token;

	token = *tok;
	while (token)
	{
		if (token && (token->type == D_QUOTE || token->type == S_QUOTE))
			if (!pass_quote_word(&token))
				return (manage_syntax_error(D_QUOTE, tok));
		if (token && token->type >= REDIREC_IN && token->type <= HEREDOC)
			if (!check_redirec_word(tok, &token))
				return (manage_syntax_error(REDIREC_IN, tok));
		if (token && token->type == PIPE)
			if (!check_pipe(token))
				return (manage_syntax_error(PIPE, tok));
		token = token->next;
	}
	if (!join_heredoc_delimiter(tok) || !join_quotes(tok, env)
		|| !change_dollars(tok, env))
		return (malloc_error(tok));
	return (1);
}
