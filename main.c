/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:45:52 by ael-idri          #+#    #+#             */
/*   Updated: 2022/09/05 17:23:37 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_inc_shlvl(t_env *val)
{
	int		t;
	t_env	*node;

	node = val;
	if (!node)
		return ;
	while (node)
	{
		if (ft_strcmp(node->key, "SHLVL") == 0)
			t = ft_atoi(get_env_node("SHLVL", val)->value) + 1;
		node = node->next;
	}
	if (get_env_node("SHLVL", val) && get_env_node("SHLVL", val)->value)
	{
		free(get_env_node("SHLVL", val)->value);
		get_env_node("SHLVL", val)->value = ft_itoa(t);
	}
	else
		ft_add(&val, ft_strdup("SHLVL"), ft_strdup("1"));
}

int	ft_is_builtins(t_pipe_seq *comd)
{
	if (comd->cmd->cmd)
	{
		if (ft_strcmp(comd->cmd->cmd, "cd") == 0)
			return (0);
		if (ft_strcmp(comd->cmd->cmd, "pwd") == 0)
			return (0);
		if (ft_strcmp(comd->cmd->cmd, "env") == 0)
			return (0);
		if (ft_strcmp(comd->cmd->cmd, "export") == 0)
			return (0);
		if (ft_strcmp(comd->cmd->cmd, "echo") == 0)
			return (0);
		if (ft_strcmp(comd->cmd->cmd, "exit") == 0)
			return (0);
		if (ft_strcmp(comd->cmd->cmd, "unset") == 0)
			return (0);
	}
	return (1);
}

void	is_builtins(t_pipe_seq *comd, t_env **p)
{
	if (ft_strcmp(comd->cmd->cmd, "cd") == 0)
		builtin_cd(comd, *p);
	else if (ft_strcmp(comd->cmd->cmd, "pwd") == 0)
		builtin_pwd(*p);
	else if (ft_strcmp(comd->cmd->cmd, "env") == 0)
		builtin_env(*p);
	else if (ft_strcmp(comd->cmd->cmd, "export") == 0)
		builtin_export(p, comd);
	else if (ft_strcmp(comd->cmd->cmd, "echo") == 0)
		builtin_echo(comd);
	else if (ft_strcmp(comd->cmd->cmd, "exit") == 0)
		bultins_exit(comd);
	else if (ft_strcmp(comd->cmd->cmd, "unset") == 0)
		builtin_unset(comd, p);
}

static void	minishell_loop(t_env *p)
{
	char		*line;
	t_token		*token;
	t_pipe_seq	*pipe_seq;

	token = NULL;
	pipe_seq = NULL;
	while (1)
	{
		g_global.herdoc = 0;
		g_global.exit_signal = 0;
		free_pipe_seq(&pipe_seq);
		line = readline("minishell$ ");
		add_history(line);
		if (!tokenizer(line, &token))
			continue ;
		free_line(&line);
		if (!syntax_error(&token, p) || !token || !parser(&token, &pipe_seq))
			continue ;
		g_global.errno = 0;
		ft_execution(&p, pipe_seq);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*p;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	p = list_env(env);
	ft_inc_shlvl(p);
	minishell_signal();
	minishell_loop(p);
	free_t_env(p);
	return (g_global.errno);
}
