/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:24:04 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/28 18:43:59 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_is_redirection(t_pipe_seq **p, t_env *env)
{
	t_pipe_seq	*pi;

	pi = *p;
	while (pi)
	{
		pi->input = -1;
		pi->output = -1;
		if (pi->cmd->cmd_pref != NULL)
			ft_multiple_redirection_pref(pi, env);
		if (pi->cmd->cmd_suff->redirection)
			ft_multiple_redirection(pi, env);
		pi = pi->next;
	}
}

void	input_herdoc(t_pipe_seq *p, t_ioredirect *cmd, t_env *env)
{
	char	*name_file;

	while (cmd)
	{
		if (cmd->type == HEREDOC)
		{
			name_file = ft_strjoin("/tmp/", cmd->file_name);
			ft_herdoc(cmd->file_name, p, env);
			if (!cmd->next)
				p->input = open(name_file, O_RDONLY, 0777);
			free(name_file);
		}
		cmd = cmd->next;
	}
}

void	ft_multiple_redirection(t_pipe_seq *p, t_env *env)
{
	t_ioredirect	*cmd;

	cmd = p->cmd->cmd_suff->redirection;
	input_herdoc(p, cmd, env);
	cmd = p->cmd->cmd_suff->redirection;
	while (cmd)
	{
		if (cmd->type == REDIREC_IN)
		{
			p->input = open(cmd->file_name, O_RDONLY, 0777);
			if (p->input == -1)
			{
				p->test = 1;
				perror (cmd->file_name);
				break ;
			}
		}
		if (cmd->type == REDIREC_OUT)
			p->output = open(cmd->file_name,
					O_TRUNC | O_CREAT | O_WRONLY, 0777);
		if (cmd->type == APPEND)
			p->output = open(cmd->file_name,
					O_CREAT | O_WRONLY | O_APPEND, 0777);
		cmd = cmd->next;
	}
}

void	ft_multiple_redirection_pref(t_pipe_seq *p, t_env *env)
{
	t_ioredirect	*cmd;

	cmd = p->cmd->cmd_pref;
	input_herdoc(p, cmd, env);
	cmd = p->cmd->cmd_pref;
	while (cmd)
	{
		if (cmd->type == REDIREC_IN)
		{
			p->input = open(cmd->file_name, O_RDONLY, 0777);
			if (p->input == -1)
			{
				p->test = 1;
				perror (cmd->file_name);
				break ;
			}
		}
		if (cmd->type == REDIREC_OUT)
			p->output = open(cmd->file_name,
					O_TRUNC | O_CREAT | O_WRONLY, 0777);
		if (cmd->type == APPEND)
			p->output = open(cmd->file_name,
					O_CREAT | O_WRONLY | O_APPEND, 0777);
		cmd = cmd->next;
	}
}
