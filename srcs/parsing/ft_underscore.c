/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_underscore.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:33:21 by dso               #+#    #+#             */
/*   Updated: 2022/03/01 12:52:13 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	d_check_underscore(t_cmds *cmd, t_minishell *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!cmd->cmd[0])
		return ;
	while (cmd->cmd[i])
		i++;
	i--;
	while (m->g_mini_env[j])
	{
		if (m->g_mini_env[j][0] == '_' && m->g_mini_env[j][1] == '=')
		{
			free(m->g_mini_env[j]);
			m->g_mini_env[j] = ft_strjoin("_=", cmd->cmd[i]);
			return ;
		}
		j++;
	}
}

void	d_replace_underscore(t_minishell *m)
{
	int	i;

	i = 0;
	while (m->g_mini_env[i])
	{
		if (m->g_mini_env[i][0] == '_' && m->g_mini_env[i][1] == '=')
		{
			free(m->g_mini_env[i]);
			m->g_mini_env[i] = d_strdup("_=/usr/bin/env");
			return ;
		}
		i++;
	}
}
