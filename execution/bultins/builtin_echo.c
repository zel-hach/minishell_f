/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:13:06 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/25 19:48:48 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_arg(char *args)
{
	int		i;
	char	*t;

	i = 1;
	t = args;
	if (!t[i])
		return (0);
	while (t && t[0] && t[i])
	{
		if (t[0] == '-' && t[1] != '-' && t[i] == 'n')
			return (1);
		else
			i++;
	}
	return (0);
}

void	is_args(char **args, int *i)
{
	int	len;

	len = ft_strlen_deux(args);
	while (args && args[*i] && *i < len - 1)
	{
		if (ft_strcmp(args[0], "-n") == 0 || ft_strcmp(args[0], "\'") == 0)
		{
			ft_putstr_fd(args[*i], 1);
			if (!args[*i + 1] && ft_strcmp(args[0], "-n") != 0)
				write(1, "\n", 1);
		}
		else if (ft_strcmp(args[*i], "\\") != 0)
			ft_putstr_fd(args[*i], 1);
		(*i)++;
		write(1, " ", 1);
	}
	ft_putstr_fd(args[*i], 1);
	if (check_arg(args[0]) != 1 && ft_strcmp(args[0], "0") != 0)
		write(1, "\n", 1);
	else if (args[0] && check_arg(args[0]) != 1)
		write(1, "\n", 1);
}

int	builtin_echo(t_pipe_seq *val)
{
	int		i;
	char	**args;

	i = 0;
	args = val->cmd->cmd_suff->args;
	if (!args || !args[0])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (args && args[i])
	{
		if (ft_strcmp(args[i], "-n") == 0 || check_arg(args[i]) == 1)
			i++;
		else
			break ;
	}
	if (!args && !args[i])
	{
		write(1, "\n", 1);
		return (0);
	}
	else
		is_args(args, &i);
	return (0);
}
