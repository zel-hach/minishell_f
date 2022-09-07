/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:47:34 by ael-idri          #+#    #+#             */
/*   Updated: 2022/08/25 16:29:22 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prev_is_hdoc(t_token *token)
{
	token = token->prev;
	while (token && token->type == SPACE)
		token = token->prev;
	if (token && token->type == HEREDOC)
		return (1);
	return (0);
}

t_token	*last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	free_tokens(t_token **token)
{
	t_token	*tempo;

	while (*token)
	{
		tempo = *token;
		*token = (*token)->next;
		free(tempo->data);
		free(tempo);
	}
}

char	*get_env_value(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(str, env->key))
		{
			if (env->value)
				return (ft_strdup(env->value));
			else
				return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

char	*join_quotes_data(char **s1, char *s2)
{
	char	*ret;

	if (!(*s1) && !s2)
		return (NULL);
	if (!(*s1))
		return (ft_strdup(s2));
	if (!s2)
		return (*s1);
	ret = (char *)malloc(ft_strlen(*s1) + ft_strlen(s2)+ 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, *s1, ft_strlen(*s1));
	ft_memcpy(ret + ft_strlen(*s1), s2, ft_strlen(s2));
	ret[ft_strlen(*s1) + ft_strlen(s2)] = '\0';
	free (*s1);
	return (ret);
}
