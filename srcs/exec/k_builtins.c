/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:58:40 by dso               #+#    #+#             */
/*   Updated: 2022/03/02 12:57:28 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	k_exec_builtins_cmd(char **cmd, t_minishell *minishell, int len)
{
	if (!d_strncmp(cmd[0], "echo", len))
		ft_echo(cmd);
	else if (!d_strncmp(cmd[0], "cd", len))
		exit(0);
	else if (!d_strncmp(cmd[0], "pwd", len))
		ft_pwd(cmd, minishell);
	else if (!d_strncmp(cmd[0], "export", len))
		exit(0);
	else if (!d_strncmp(cmd[0], "unset", len))
		exit(0);
}

void	k_exec_builtins(char **cmd, t_minishell *minishell)
{
	int	len;
	int	i;

	len = d_strlen(cmd[0]);
	i = 0;
	k_exec_builtins_cmd(cmd, minishell, len);
	if (!d_strncmp(cmd[0], "env", len))
	{
		while (minishell->g_mini_env[i]
			&& (minishell->g_mini_env[i][0] != 'P'
			|| minishell->g_mini_env[i][1] != 'A'
			|| minishell->g_mini_env[i][2] != 'T'
			|| minishell->g_mini_env[i][3] != 'H'))
		i++;
		if (minishell->g_mini_env[i])
			ft_env(cmd, minishell);
		else
			ft_error(cmd[0], "No such file or directory");
	}
	else if (!d_strncmp(cmd[0], "exit", len))
		ft_exit(minishell, cmd, 1);
}

void	k_is_builtin_fct(char **cmd, t_minishell *minishell)
{
	int	len;

	if (!cmd[0])
		return ;
	len = d_strlen(cmd[0]);
	if (!d_strncmp(cmd[0], "echo", len) || !d_strncmp(cmd[0], "cd", len)
		|| !d_strncmp(cmd[0], "pwd", len) || !d_strncmp(cmd[0], "export", len)
		|| !d_strncmp(cmd[0], "unset", len) || !d_strncmp(cmd[0], "env", len)
		|| !d_strncmp(cmd[0], "exit", len))
		k_exec_builtins(cmd, minishell);
	else
		k_exec_cmd(cmd, minishell);
}
