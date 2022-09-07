/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:57:21 by zel-hach          #+#    #+#             */
/*   Updated: 2022/08/27 20:41:59 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ret_tab(t_env *val)
{
	char	**t;
	int		i;
	t_env	*p;

	i = 0;
	p = val;
	t = malloc(sizeof(char *) * (ft_size(p) + 1));
	if (!p || !t)
		return (free(t), NULL);
	while (p)
	{
		t[i] = ft_strdup(p->key);
		i++;
		p = p->next;
	}
	t[i] = NULL;
	return (t);
}

int	ft_strlen_key(char *envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
	{
		if (envp[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_key_export(char *envp)
{
	int		i;
	char	*val;

	i = 0;
	val = malloc(sizeof(char *) * ft_strlen_key(envp));
	if (!envp || !val)
		return (NULL);
	while (envp[i])
	{
		if (envp[i] == '+' && envp[i + 1] == '=')
			return (val);
		else if (envp[i] == '=')
			return (val);
		else
		{
			val[i] = envp[i];
			i++;
		}
	}
	return (val);
}

void	ft_tri(char **tab)
{
	char	*t;
	char	**tableau;
	int		i;
	int		j;

	i = 0;
	tableau = tab;
	while (tableau && tableau[i])
	{
		j = i + 1;
		while (tableau[j])
		{
			if (strcmp(tableau[i], tableau[j]) > 0)
			{
				t = tableau[i];
				tableau[i] = tableau[j];
				tableau[j] = t;
			}
			j++;
		}
		i++;
	}
}

int	check_erreur_in_export(char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	if (!key)
		return (1);
	if (key[len - 2] == '+' && key[len - 1] == '+')
		return (0);
	while (key[i])
	{
		if (ft_isdigit(key[0]))
		{
			return (0);
		}
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != ' ')
		{
			return (0);
		}
		i++;
	}
	return (1);
}
