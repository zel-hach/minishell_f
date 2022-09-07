/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_non_bultins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:21:50 by zel-hach          #+#    #+#             */
/*   Updated: 2022/09/05 17:14:38 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_perror(t_pipe_seq *cmd)
{
	perror(cmd->cmd->cmd);
	exit(127);
}

int	ft_size(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**env_to_str(t_env *env)
{
	char	**tab;
	char	**t;
	int		i;

	i = 0;
	tab = (char **)ft_calloc(ft_size(env) + 1, sizeof(char *));
	t = (char **)ft_calloc(ft_size(env) + 1, sizeof(char *));
	if (!tab || !t)
		perror("error allocation");
	while (env)
	{
		t[i] = ft_strjoin(env->key, "=");
		tab[i] = ft_strjoin(t[i], env->value);
		i++;
		env = env->next;
	}
	free_tab(&t);
	return (tab);
}

int	ft_strlen_deux(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}
