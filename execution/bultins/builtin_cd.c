/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:25:41 by zel-hach          #+#    #+#             */
/*   Updated: 2022/09/07 17:48:04 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_args_not_exist(t_env *head,	t_env *pwd, t_env *oldpwd)
{
	char	*old;

	chdir(get_env_node("HOME", head)->value);
	old = pwd->value;
	pwd->value = get_env_node("HOME", head)->value;
	free(oldpwd->value);
	oldpwd->value = old;
}

void	builtin_cd(t_pipe_seq *arg, t_env *head)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = get_env_node("PWD", head);
	oldpwd = get_env_node("OLDPWD", head);
	if (pwd && oldpwd)
	{
		if (!arg->cmd->cmd_suff->args)
		{
			if (!get_env_node("HOME", head))
				ft_putstr_fd("bash: cd: HOME not set\n", 2);
			else
				cd_args_not_exist(head, pwd, oldpwd);
		}
		else
			ft_cd(arg, pwd, oldpwd);
	}
	else
		ft_is_pwd_deleted(arg, head);
}
