/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:45:12 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/28 13:31:08 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_value(t_env	*node, char	*value)
{
	if (value)
	{
		if (node->value)
			free(node->value);
		node->value = ft_strdup(value);
		free(value);
	}
}

void	add_env(t_env **val, char *args)
{
	t_env	*node;
	char	*key;
	char	*value;

	key = ft_key_export(args);
	value = ft_strdup(ft_strchr(args, '='));
	node = get_env_node(key, (*val));
	if (node == NULL)
		ft_add(val, key, value);
	else if (ft_strchr1(args, '=') == 1)
	{
		node->value = join_quotes_data(&node->value, value);
		free(value);
		free(key);
	}
	else
	{
		change_value(node, value);
		free(key);
	}
}

void	add_arg_in_export(t_pipe_seq *cmd, t_env **val)
{
	char	**args;
	char	*key;
	int		i;

	i = 0;
	args = cmd->cmd->cmd_suff->args;
	while (args[i])
	{
		key = ft_key_export(args[i]);
		if (!check_erreur_in_export(key))
		{
			ft_putstr_fd("bash:", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
		else
			add_env(val, args[i]);
		free(key);
		i++;
	}
}

int	ft_export(t_env **val)
{
	char	**tab;
	int		i;

	tab = ret_tab(*val);
	i = 0;
	if (!tab)
		return (free_tab(&tab), 0);
	ft_tri(tab);
	while (tab[i])
	{
		if (get_env_node(tab[i], (*val))->value != NULL)
		{
			printf("declare -x %s=\"%s\"\n", tab[i],
				get_env_node(tab[i], (*val))->value);
		}
		else if (ft_strchr1(tab[i], '=') == 2)
			printf("declare -x %s=\"\"\n", tab[i]);
		else
			printf("declare -x %s\n", tab[i]);
		i++;
	}
	free_tab(&tab);
	return (0);
}

int	*builtin_export(t_env **val, t_pipe_seq *cmd)
{
	if (cmd->cmd->cmd_suff->args)
		add_arg_in_export(cmd, val);
	else if (!cmd->cmd->cmd_suff->args)
		ft_export(val);
	return (0);
}
