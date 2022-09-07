/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:11:21 by zel-hach          #+#    #+#             */
/*   Updated: 2022/09/07 17:49:05 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	swap_pwd(t_env *pwd, t_env *oldpwd)
{
	char	*old;

	old = pwd->value;
	pwd->value = oldpwd->value;
	oldpwd->value = old;
}

void	ft_is_moins(t_pipe_seq *arg, t_env *pwd, t_env *oldpwd, char *args)
{
	char	cwd[PATH_MAX];

	if (ft_strcmp(*arg->cmd->cmd_suff->args, "-") == 0)
	{
		swap_pwd(pwd, oldpwd);
		printf("%s\n", pwd->value);
		chdir(pwd->value);
	}
	else if (getcwd(cwd, PATH_MAX) == NULL
		&& ft_strcmp(*arg->cmd->cmd_suff->args, "..") == 0)
	{
		swap_pwd(pwd, oldpwd);
		chdir(pwd->value);
	}
	else
	{
		g_global.errno = 1;
		perror(args);
	}
}

void	delete_derectory(t_pipe_seq *arg, t_env	*pwd, t_env	*oldpwd, char *cwd)
{
	if (ft_strcmp(*arg->cmd->cmd_suff->args, ".") == 0)
		pwd->value = ft_strjoin(cwd, "/.");
	else if (ft_strcmp(*arg->cmd->cmd_suff->args, "..") == 0)
	{
		pwd->value = ft_strjoin(oldpwd->value, "/..");
		ft_putstr_fd("cd: error retrieving current directory", 2);
		ft_putstr_fd(":getcwd: cannot access parent directories:", 2);
	}
	perror(*arg->cmd->cmd_suff->args);
}

void	ft_cd(t_pipe_seq *arg,	t_env	*pwd, t_env	*oldpwd)
{
	char	*args;
	char	cwd[PATH_MAX];

	args = *arg->cmd->cmd_suff->args;
	if (chdir(args) == -1)
		ft_is_moins(arg, pwd, oldpwd, args);
	else
	{
		if (oldpwd->value)
			free(oldpwd->value);
		oldpwd->value = pwd->value;
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			delete_derectory(arg, pwd, oldpwd, cwd);
		else
			pwd->value = ft_strdup(cwd);
	}
}

void	ft_is_pwd_deleted(t_pipe_seq *arg, t_env *val)
{
	t_env	*home;

	if (!arg->cmd->cmd_suff->args)
	{
		home = get_env_node("HOME", val);
		if (!home)
			ft_putstr_fd("bash: cd: HOME not set\n", 2);
		else
			chdir(home->value);
	}
	else
	{
		if (chdir(*arg->cmd->cmd_suff->args) == -1)
		{
			if (ft_strcmp(*arg->cmd->cmd_suff->args, "-") == 0)
				ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			else
			{
				g_global.errno = 1;
				perror(*arg->cmd->cmd_suff->args);
			}
		}
		add_pwd_old(val);
	}
}
