/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:22:33 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/29 16:25:57 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_first(t_env **env)
{
	t_env	*temp;

	if (!(*env))
		return ;
	else
	{
		temp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free((*env));
		(*env) = temp;
	}
}

int	check_erreur_in_unset(char *args)
{
	int	i;

	i = 0;
	if (!args)
		return (1);
	while (args && args[i])
	{
		if (ft_isdigit(args[0]))
			return (0);
		if (!ft_isalnum(args[i]) && args[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(t_env **val, char *args)
{
	t_env	*head;
	t_env	*next;

	head = *val;
	if (!head)
		return ;
	while (head)
	{
		if (head->next && ft_strcmp(head->next->key, args) == 0)
		{
			next = head->next;
			if (head->next->next)
				head->next = head->next->next;
			else
				head->next = NULL;
			free(next->key);
			free(next->value);
			free(next);
			break ;
		}
		head = head->next;
	}
}

int	builtin_unset(t_pipe_seq *arg, t_env **val)
{
	char	**args;

	args = arg->cmd->cmd_suff->args;
	if (!args)
		return (0);
	while (args && *args)
	{
		if (check_erreur_in_unset(*args) == 0)
		{
			ft_putstr_fd("bash:", 2);
			ft_putstr_fd(*args, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
		if (!(*val))
			return (0);
		else if (ft_strcmp((*val)->key, *args) == 0)
		{
			free_first(val);
			return (0);
		}
		else
			ft_unset(val, *args);
		args++;
	}
	return (0);
}
