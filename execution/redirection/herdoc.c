/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:33:38 by zel-hach          #+#    #+#             */
/*   Updated: 2022/09/05 19:20:36 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_herdoc(int fd, char *name_file, char *buf)
{
	free(name_file);
	free(buf);
	close(fd);
	exit (1);
}

int	write_token(t_token **token, int fd, t_env *env)
{
	t_token	*run;

	if (!change_dollars(token, env))
		return (malloc_error(token));
	run = *token;
	while (run)
	{
		write(fd, run->data, ft_strlen(run->data));
		run = run->next;
	}
	return (0);
}

int	write_in_herdoc(char *dilemiter, t_env *env)
{
	char	*buf;
	t_token	*token;
	int		fd;
	char	*name_file;

	token = NULL;
	name_file = ft_strjoin("/tmp/", dilemiter);
	herdoc_signal_handler();
	fd = open(name_file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	buf = readline(" > ");
	while (1)
	{
		if (buf == NULL || ft_strcmp(buf, dilemiter) == 0)
			exit (0);
		tokenizer(buf, &token);
		write_token(&token, fd, env);
		write(fd, "\n", 1);
		free_tokens(&token);
		buf = readline(" > ");
	}
	return (free_herdoc(fd, name_file, buf));
}

int	ft_herdoc(char *dilemiter, t_pipe_seq *p, t_env *env)
{
	int	status;

	g_global.herdoc = 1;
	p->pid = fork();
	if (p->pid < 0)
	{
		write(2, "error\n", 6);
		exit (0);
	}
	if (p->pid == 0)
		write_in_herdoc(dilemiter, env);
	waitpid(p->pid, &status, 0);
	g_global.herdoc = 0;
	return (WEXITSTATUS(status));
}
