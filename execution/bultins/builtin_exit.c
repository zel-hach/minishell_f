/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:17:18 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/28 17:40:02 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_long(char arg, long int t)
{
	if ((arg == '-' && t > 0) || (arg != '-' && t < 0))
		return (0);
	else
		return (1);
}

void	ft_exit(char **args)
{
	int			i;
	long int	temp;

	temp = ft_atoi(*args);
	i = 0;
	while (*args[i])
	{
		if (((*args[0] != '-') && ft_isdigit(*args[i]) == 0)
			|| check_long(*args[0], temp) == 0)
		{
			write(2, "exit\n", 5);
			ft_putstr_fd("bash:", 2);
			ft_putstr_fd(*args, 2);
			ft_putstr_fd(" : numeric argument required\n", 2);
			exit (0);
		}
		else
		{
			write(2, "exit\n", 5);
			exit (temp % 256);
		}
		i++;
	}
}

void	print_exit(t_pipe_seq *p)
{
	write(2, "exit\n", 5);
	ft_putstr_fd("bash:", 2);
	ft_putstr_fd(p->cmd->cmd, 2);
	ft_putstr_fd(": too many arguments\n", 2);
}

void	ft_is_exit(t_pipe_seq *p, char **args)
{
	int			i;
	long int	temp;

	i = 0;
	temp = ft_atoi(*args);
	while (*args[i])
	{
		if (((*args[0] != '-') && ft_isdigit(*args[i]) == 0)
			|| check_long(*args[0], temp) == 0)
		{
			print_exit(p);
			exit (0);
		}
		else
		{
			print_exit(p);
			break ;
		}
	}
	i++;
}

void	bultins_exit(t_pipe_seq *p)
{
	char		**args;

	args = p->cmd->cmd_suff->args;
	if (ft_strlen_deux(args) == 1 || ft_strlen_deux(args) == 0)
	{
		if (!args)
		{
			write(2, "exit\n", 5);
			exit (g_global.errno);
		}
		ft_exit(args);
	}
	else
		ft_is_exit(p, args);
}
