/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:10:08 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/21 17:08:18 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_t_env(t_env *env)
{
	t_env	*node;

	while (env)
	{
		node = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = node;
		free(node);
	}
	free(node);
	free(env);
}

void	free_line(char **line)
{
	free(*line);
	*line = NULL;
}

void	free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (!*tab)
		return ;
	while (*tab && (*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}
