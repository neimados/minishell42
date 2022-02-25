/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_exec_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:37:42 by dso               #+#    #+#             */
/*   Updated: 2022/02/18 15:46:19 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	k_unlink_heredoc(t_minishell *minishell, pid_t *forks)
{
	t_cmds	*tmp2;

	tmp2 = minishell->cmds;
	while (tmp2)
	{
		if (tmp2->heredoc == 1)
			unlink(tmp2->infile);
		tmp2 = tmp2->next;
	}
	free(forks);
}

int	k_count_cmds(t_cmds *tmp)
{
	t_cmds	*tmp2;
	int		nbcmd;

	nbcmd = 0;
	tmp2 = tmp;
	while (tmp2)
	{
		nbcmd++;
		tmp2 = tmp2->next;
	}
	return (nbcmd);
}

void	k_join_cmd(char **path, char **cmd)
{
	int	i;

	i = 0;
	while (path && path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
		{
			d_free_tab(path);
			d_putstr_fd("malloc path failed\n", 2);
			exit(EXIT_FAILURE);
		}
		path[i] = ft_strjoin(path[i], cmd[0]);
		if (!path[i])
		{
			d_free_tab(path);
			d_putstr_fd("malloc path failed\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	k_search_path(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->g_mini_env[i] && (minishell->g_mini_env[i][0] != 'P'
		|| minishell->g_mini_env[i][1] != 'A'
		|| minishell->g_mini_env[i][2] != 'T'
		|| minishell->g_mini_env[i][3] != 'H'))
		i++;
	return (i);
}
