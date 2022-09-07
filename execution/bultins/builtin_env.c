/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:13:14 by zel-hach          #+#    #+#             */
/*   Updated: 2022/09/05 17:14:12 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	ft_strchr1(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] != '+' && str[i + 1] == '+'
			&& str[i + 2] == (unsigned char)c)
			return (1);
		if (str[i] == (unsigned char)c)
			return (2);
		i++;
	}
	return (0);
}

char	*ft_key(char *envp)
{
	int		i;
	char	*val;

	i = 0;
	val = ft_calloc(ft_strlen_key(envp) + 1, sizeof(char));
	if (!envp || !val)
		return (NULL);
	while (envp[i])
	{
		if (envp[i] == '=')
		{
			val[i] = '\0';
			return (val);
		}
		else
			val[i] = envp[i];
		i++;
	}
	return (val);
}

t_env	*ft_list(t_env *head, char **env_array)
{
	t_env	*env;
	char	*key;
	int		i;

	env = head;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		key = ft_key(env_array[i]);
		env->next = (t_env *)malloc(sizeof(t_env));
		if (!(env->next))
			return (NULL);
		env = env->next;
		env->key = ft_strdup(key);
		free(key);
		env->value = ft_strdup(getenv(env->key));
		env->next = NULL;
		i++;
	}
	return (env);
}

t_env	*list_env(char **env_array)
{
	t_env	*head;
	char	*key;

	if (!*env_array)
		return (NULL);
	key = ft_key(env_array[0]);
	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->key = ft_strdup(key);
	free(key);
	if (!getenv(head->key))
		head->value = NULL;
	head->value = ft_strdup(getenv(head->key));
	ft_list(head, env_array);
	return (head);
}

int	*builtin_env(t_env *val)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ret_tab(val);
	while (tab && tab[i])
	{
		if (get_env_node(tab[i], val)->value != NULL)
			printf("%s=%s\n", tab[i], get_env_node(tab[i], val)->value);
		else if (ft_strchr1(tab[i], '=') == 1)
			printf("%s=\n", tab[i]);
		i++;
	}
	free_tab(&tab);
	return (0);
}
