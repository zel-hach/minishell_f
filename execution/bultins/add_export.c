/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:40:53 by zel-hach          #+#    #+#             */
/*   Updated: 2022/09/05 17:13:43 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_add(t_env **val, char *key, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	tmp = (*val);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		perror("error allocation");
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (!tmp)
	{
		*val = new_node;
		return ;
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_env	*get_env_node(char *str, t_env *head)
{
	t_env	*node;

	node = head;
	if (!node)
		return (NULL);
	while (node && node->key)
	{
		if (ft_strcmp(node->key, str) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	add_pwd_old(t_env *val)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		if (!get_env_node("OLDPWD", val))
			ft_add(&val, ft_strdup("OLDPWD"), ft_strdup(cwd));
		if (!get_env_node("OLDPWD", val))
			ft_add(&val, ft_strdup("PWD"), ft_strdup(cwd));
	}
}
