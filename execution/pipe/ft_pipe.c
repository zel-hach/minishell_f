/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:47:42 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/28 18:43:10 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	wait_pid(int status)
{
	g_global.in_child = 0;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			g_global.errno = WTERMSIG(status) + 128;
		if (WTERMSIG(status) == 3)
			g_global.errno = WTERMSIG(status) + 128;
	}
	else
		g_global.errno = WEXITSTATUS(status);
	return (g_global.errno);
}

void	dup_file(t_pipe_seq *pi, t_info *info)
{
	if (pi->input != -1)
	{
		dup2(pi->input, STDIN_FILENO);
		close(pi->input);
	}
	if (pi->output != -1)
	{
		dup2(pi->output, STDOUT_FILENO);
		close(pi->output);
	}
	else if (pi->input == -1 && pi->output == -1)
	{
		dup2(info->in, 0);
		close(info->in);
	}
}

void	ft_execute_pipe(t_pipe_seq *pi, t_env *env)
{
	if (ft_is_builtins(pi) == 0)
	{
		is_builtins(pi, &env);
		exit (0);
	}
	else
	{
		if (!pi->cmd->cmd)
			exit(0);
		if (pi->test == 1)
			exit (1);
		else
		{
			ft_exec(&env, pi);
			ft_putstr_fd("bash:", 2);
			ft_putstr_fd(pi->cmd->cmd, 2);
			ft_putstr_fd(":command not found\n", 2);
			exit (127);
		}
	}
}

void	fork_pipe(t_pipe_seq *pi, t_env *env, t_info *info)
{
	info->pfd[1] = 1;
	if (pi->next)
		pipe(info->pfd);
	pi->pid = fork();
	if (pi->pid < 0)
	{
		ft_putstr_fd("bash:", 2);
		ft_putstr_fd("fork : Resource temporarily unavailable\n", 2);
		info->erreur_fork = 1;
	}
	else if (pi->pid == 0)
	{
		if (g_global.exit_signal == 1)
			exit (0);
		if (pi->next)
		{
			dup2(info->pfd[1], 1);
			close(info->pfd[1]);
		}
		dup_file(pi, info);
		if (pi->input == -1)
			close(info->pfd[0]);
		ft_execute_pipe(pi, env);
	}
}

int	ft_pipe(t_env *env, t_pipe_seq **p, t_info	*info)
{
	t_pipe_seq	*pi;

	info->in = dup(0);
	info->status = 0;
	ft_is_redirection(p, env);
	pi = *p;
	while (pi)
	{
		g_global.in_child = 1;
		fork_pipe(pi, env, info);
		if (info->erreur_fork == 1)
			return (1);
		if (pi->next)
			close(info->pfd[1]);
		if (pi->input != -1 && pi->next)
			pi->input = info->pfd[0];
		close(info->in);
		info->in = info->pfd[0];
		if (pi->next == NULL)
			waitpid(pi->pid, &info->status, 0);
		pi = pi->next;
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (wait_pid(info->status));
}
