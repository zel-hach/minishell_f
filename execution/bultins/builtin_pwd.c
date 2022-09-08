/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:13:34 by zel-hach          #+#    #+#             */
/*   Updated: 2022/09/08 18:07:56 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	builtin_pwd(t_env *val)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else if (get_env_node("PWD", val))
		printf("%s\n", get_env_node("PWD", val)->value);
	else if (!get_env_node("PWD", val) && getcwd(cwd, sizeof(cwd)))
	{
		ft_add(&val, ft_strdup("PWD"), ft_strdup(cwd));
		printf("%s\n", cwd);
	}
	printf("%s\n",getcwd(cwd,PATH_MAX));
}
