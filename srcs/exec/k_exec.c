/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:05:49 by kmammeri          #+#    #+#             */
/*   Updated: 2022/02/18 17:06:11 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	k_exec_cmd(char **cmd, t_minishell *minishell)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	if (access(cmd[i], X_OK) == 0)
		execve(cmd[i], cmd, minishell->g_mini_env);
	i = k_search_path(minishell);
	if (minishell->g_mini_env[i])
		path = ft_split(minishell->g_mini_env[i] + 5, ':');
	else
		ft_error(cmd[0], "No such file or directory");
	k_join_cmd(path, cmd);
	i = -1;
	while (path && path[++i])
	{
		if (access(path[i], X_OK) == 0)
			execve(path[i], cmd, minishell->g_mini_env);
	}
	d_free_tab(path);
	free(g_error[0]);
	g_error[0] = d_strdup("127");
	ft_error(cmd[0], "command not found");
}

void	k_loop_forks(t_minishell *minishell)
{
	int		i;
	int		nbcmd;
	pid_t	*forks;
	t_cmds	*tmp;
	t_cmds	*tmp2;

	tmp = minishell->cmds;
	tmp2 = tmp;
	nbcmd = k_count_cmds(tmp);
	i = d_strlen(tmp->cmd[0]);
	if (k_loop_forks_check(nbcmd, minishell, tmp, i) == 1)
		return ;
	k_set_signals(nbcmd, tmp, i);
	forks = malloc(sizeof(pid_t) * nbcmd);
	if (!forks)
	{
		d_putstr_fd("minishell: fork failed\n", 2);
		return ;
	}
	i = k_create_forks(nbcmd, tmp, minishell, forks);
	if (i == -1)
		return ;
	k_forks_end((i - 1), minishell, tmp2, forks);
	k_unlink_heredoc(minishell, forks);
	return ;
}
