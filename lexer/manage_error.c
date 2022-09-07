/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:15:53 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/30 18:47:04 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	malloc_error(t_token **token)
{
	free_tokens(token);
	g_global.errno = 1;
	printf("malloc error !!\n");
	return (0);
}

int	manage_syntax_error(int type, t_token **token)
{
	g_global.errno = 258;
	free_tokens(token);
	if (type == D_QUOTE)
		ft_putstr_fd("syntax error : near quote\n", 2);
	if (type == PIPE)
		ft_putstr_fd("syntax error : near '|'\n", 2);
	if (type == REDIREC_IN)
		ft_putstr_fd("syntax error : near redirect or append  or heredoc\n", 2);
	return (0);
}
