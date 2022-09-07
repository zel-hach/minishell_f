/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:10:16 by ael-idri          #+#    #+#             */
/*   Updated: 2022/09/05 17:23:25 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	herdoc(int signum)
{
	(void)signum;
	exit(130);
}

void	kill_handler(int signum)
{
	g_global.errno = 1;
	if (signum == SIGINT)
	{
		if (g_global.in_child == 1)
			return ;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_global.herdoc)
		{
			g_global.exit_signal = 1;
			return ;
		}
		rl_redisplay();
	}
}

void	herdoc_signal_handler(void)
{
	rl_catch_signals = 1;
	signal(SIGINT, herdoc);
	signal(SIGQUIT, SIG_IGN);
}

void	quit_handler(int signum)
{
	(void)signum;
	if (g_global.in_child == 1 || g_global.herdoc == 1)
	{
		g_global.exit_signal = 1;
		write(1, "Quit: 3\n", 8);
		return ;
	}
}

void	minishell_signal(void)
{
	signal(SIGINT, kill_handler);
	signal(SIGQUIT, quit_handler);
}
