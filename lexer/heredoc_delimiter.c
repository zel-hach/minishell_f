/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:04:44 by ael-idri          #+#    #+#             */
/*   Updated: 2022/08/25 16:21:43 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_data_in_quote_to_delimiter(t_token **token, char **delim, int quot_type)
{
	(*token) = (*token)->next;
	if ((*token)->type == quot_type)
	{
		*delim = join_quotes_data(delim, "");
		*token = (*token)->next;
	}
	while (*token && (*token)->type != quot_type)
	{
		*delim = join_quotes_data(delim, (*token)->data);
		*token = (*token)->next;
	}
	return (1);
}

void	get_delimiter_data(t_token **token, char **delimiter)
{
	if ((*token)->next && (*token)->type == DOLLAR
		&& ((*token)->next->type == S_QUOTE || (*token)->next->type == D_QUOTE))
		(*token) = (*token)->next;
	while (*token && ((*token)->type != SPACE && (*token)->type != PIPE
			&& (*token)->type < REDIREC_IN))
	{
		if ((*token)->type == D_QUOTE)
		{
			if (!add_data_in_quote_to_delimiter(token, delimiter, D_QUOTE))
				continue ;
		}
		else if ((*token)->type == S_QUOTE)
		{
			if (!add_data_in_quote_to_delimiter(token, delimiter, S_QUOTE))
				continue ;
		}
		else
			*delimiter = join_quotes_data(delimiter, (*token)->data);
		if (*token)
			*token = (*token)->next;
	}
}

t_token	*new_delimiter(t_token **token)
{
	t_token	*delim;

	delim = (t_token *)malloc(sizeof(t_token));
	if (!delim)
		return (NULL);
	delim->type = WORD;
	delim->data = NULL;
	delim->next = NULL;
	delim->prev = (*token)->prev;
	(*token)->prev->next = delim;
	return (delim);
}

int	create_delimiter(t_token **token)
{
	t_token	*tem;
	t_token	*delim;

	delim = new_delimiter(token);
	if (!delim)
		return (0);
	tem = *token;
	get_delimiter_data(token, &delim->data);
	delim->next = *token;
	if (*token)
	{
		(*token)->prev->next = NULL;
		(*token)->prev = delim;
	}
	free_tokens(&tem);
	return (1);
}

int	join_heredoc_delimiter(t_token **token)
{
	t_token	*run;

	run = (*token);
	while (run)
	{
		while (run && run->type != HEREDOC)
			run = run->next;
		if (!run)
			return (1);
		run = run->next;
		while (run && run->type == SPACE)
			run = run->next;
		if (!create_delimiter(&run))
			return (0);
	}
	return (1);
}
