/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_child_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:49:26 by dso               #+#    #+#             */
/*   Updated: 2022/03/02 18:29:39 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	k_child_fd(t_cmds *tmp, t_minishell *minishell)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	k_child_dup(tmp, in, out);
	if (tmp->next)
	{
		if (dup2(tmp->next->pipe[1], STDOUT_FILENO) == -1)
			return ;
		close(tmp->next->pipe[1]);
	}
	k_is_builtin_fct(tmp->cmd, minishell);
}

t_cmds	*k_child_close_pipe(int i, t_cmds *tmp)
{
	while (tmp && i - 1 > 0)
	{
		if (tmp->next)
		{
			close(tmp->next->pipe[0]);
			close(tmp->next->pipe[1]);
		}
		tmp = tmp->next;
		i--;
	}
	return (tmp);
}

void	k_set_gerror(void)
{
	d_free_tab(g_error);
	g_error = d_calloc(3, sizeof(char *));
	if (!g_error)
		return ;
	g_error[0] = d_strdup("1");
}

void	k_child_error_exit(t_cmds *tmp)
{
	k_set_gerror();
	ft_error(tmp->infile, strerror(errno));
}
