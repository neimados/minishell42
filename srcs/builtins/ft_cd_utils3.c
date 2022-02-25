/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:43:55 by dso               #+#    #+#             */
/*   Updated: 2022/02/23 18:18:03 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	k_cd_ignore(char **tmp2, char **cmds)
{
	if (!tmp2)
		return (1);
	if (cmds[1])
	{
		if (!d_strncmp(cmds[1], ".", 1) || !cmds[1][0])
		{
			return (1);
		}
	}
	return (0);
}

int	k_cd_slash(t_minishell *minishell, int j, char **cmds)
{
	if (j != -1)
		free(minishell->g_mini_env[j]);
	free(minishell->pwd);
	if (cmds[1][ft_strlen(cmds[1]) - 1] == '/' && ft_strlen(cmds[1]) != 1)
	{
		minishell->pwd = d_substr(cmds[1], 0, ft_strlen(cmds[1]) - 1);
		if (!minishell->pwd)
			return (1);
	}
	else
	{
		minishell->pwd = ft_strjoin(cmds[1], "\0");
		if (!minishell->pwd)
			return (1);
	}
	if (j != -1)
		minishell->g_mini_env[j] = ft_strjoin("PWD=", minishell->pwd);
	if (j != -1 && !minishell->g_mini_env[j])
		return (1);
	return (0);
}

int	k_cd_others(t_minishell *minishell, int j, char **cmds, char *tmp)
{
	if (j != -1)
		free(minishell->g_mini_env[j]);
	if (!d_strncmp("/", minishell->pwd, d_strlen(minishell->pwd)))
		tmp = ft_strdup(minishell->pwd);
	else
		tmp = ft_strjoin(minishell->pwd, "/");
	if (!tmp)
		return (1);
	if (cmds[1][ft_strlen(cmds[1]) - 1] == '/' && ft_strlen(cmds[1]) != 1)
	{
		tmp = d_strjoin(tmp, cmds[1]);
		minishell->pwd = d_substr(tmp, 0, d_strlen(tmp) - 1);
	}
	else
		minishell->pwd = ft_strjoin(tmp, cmds[1]);
	if (!minishell->pwd)
		return (1);
	if (j != -1)
	{
		minishell->g_mini_env[j] = ft_strjoin("PWD=", minishell->pwd);
		if (!minishell->g_mini_env[j])
			return (1);
		free(tmp);
	}
	return (0);
}

int	k_cd_type2(t_minishell *minishell, int j, char **cmds)
{
	if (!cmds[1] || !d_strncmp(cmds[1], "--", d_strlen(cmds[1]))
		|| !d_strncmp(cmds[1], "~", d_strlen(cmds[1])))
	{
		if (k_cd_user(minishell, j) == 1)
			return (-1);
		return (2);
	}
	else if (!d_strncmp(cmds[1], "..", d_strlen(cmds[1])))
	{
		if (k_cd_dotdot(minishell, j) == 1)
			return (-1);
		return (2);
	}
	else if (!d_strncmp(cmds[1], "-", d_strlen(cmds[1])))
	{
		if (k_cd_dash(minishell, j) == 1)
			return (-1);
		return (2);
	}
	return (0);
}

int	k_cd_type(t_minishell *minishell, char **cmds, int j)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = k_cd_type2(minishell, j, cmds);
	if (i == -1)
		return (1);
	else if (i == 2)
		return (0);
	if (cmds[1][0] == '/')
	{
		if (k_cd_slash(minishell, j, cmds) == 1)
			return (1);
	}
	else
	{
		if (k_cd_others(minishell, j, cmds, tmp) == 1)
			return (1);
	}
	free(tmp);
	return (0);
}
