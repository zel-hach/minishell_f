/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:17:29 by zel-hach          #+#    #+#             */
/*   Updated: 2022/09/05 17:12:25 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execution(t_env **p, t_pipe_seq *pipe_seq)
{
	t_info		*info;

	info = malloc(sizeof(t_info));
	if (!info)
		perror("error allocation");
	if ((pipe_seq && pipe_seq->next == NULL
			&& (pipe_seq->cmd->cmd_suff->redirection == NULL
				&& pipe_seq->cmd->cmd_pref == NULL)))
	{
		if (ft_is_builtins(pipe_seq) == 0)
			is_builtins(pipe_seq, p);
		else
			ft_main_execv(p, pipe_seq);
	}
	else
		ft_pipe(*p, &pipe_seq, info);
	free(info);
}

char	**join_arg_cmd(t_pipe_seq *p)
{
	t_info_join	*inf_join;

	inf_join = malloc(sizeof(t_info_join));
	if (!inf_join)
		perror("error allocation");
	inf_join->j = 1;
	inf_join->len = ft_strlen_deux (p->cmd->cmd_suff->args);
	inf_join->join_arg = malloc(sizeof(char *) * (inf_join->len + 2));
	inf_join->join_arg[inf_join->len + 1] = NULL;
	inf_join->join_arg[0] = ft_strdup(p->cmd->cmd);
	inf_join->args = p->cmd->cmd_suff->args;
	inf_join->i = 0;
	if (!inf_join->args)
		return (&inf_join->join_arg[0]);
	while (inf_join->args[inf_join->i])
	{
		inf_join->join_arg[inf_join->j] = inf_join->args[inf_join->i];
		inf_join->i++;
		inf_join->j++;
	}
	return (inf_join->join_arg);
}

int	ft_access(t_env *env, t_pipe_seq *cmd, char **args, char **envp)
{
	char	**split_command;
	char	*join_slash;
	char	*join_command;
	int		i;

	i = 0;
	split_command = ft_split(env->value, ':');
	while (split_command[i++])
	{
		if (split_command[i] == NULL)
			join_slash = ft_strjoin(env->value, "/");
		else
			join_slash = ft_strjoin(split_command[i], "/");
		join_command = ft_strjoin(join_slash, cmd->cmd->cmd);
		if (access(join_command, F_OK) == 0)
			return (execve(join_command, args, envp));
	}
	return (0);
}

int	ft_exec(t_env **env, t_pipe_seq *cmd)
{
	char	**args;
	char	**envp;
	t_env	*head;

	envp = env_to_str(*env);
	args = join_arg_cmd(cmd);
	head = (*env);
	if (ft_strchr(cmd->cmd->cmd, '/') != NULL)
	{
		if (access(cmd->cmd->cmd, F_OK) != 0)
			ft_perror(cmd);
		else
			return (execve(cmd->cmd->cmd, args, envp));
	}
	else
	{
		while (head)
		{
			if (ft_strcmp(head->key, "PATH") == 0)
				ft_access(head, cmd, args, envp);
			head = head->next;
		}
	}
	return (0);
}

int	ft_main_execv(t_env **env, t_pipe_seq *cmd)
{
	int	status;

	g_global.in_child = 1;
	status = 0;
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		write(2, "error\n", 6);
		exit (0);
	}
	if (cmd->pid == 0)
	{
		ft_exec(env, cmd);
		ft_putstr_fd("bash:", 2);
		ft_putstr_fd(cmd->cmd->cmd, 2);
		ft_putstr_fd(":command not found\n", 2);
		exit (127);
	}
	waitpid(cmd->pid, &status, 0);
	return (wait_pid(status));
}
