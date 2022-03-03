/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:40:58 by dso               #+#    #+#             */
/*   Updated: 2022/03/02 15:02:47 by kmammeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	k_cd_user2(int i, t_minishell *m, int j)
{
	char	*tmp;

	tmp = d_substr(m->g_mini_env[i], 5, d_strlen(m->g_mini_env[i] + 5));
	if (!tmp)
		return (1);
	if (j != -1)
		m->g_mini_env[j] = ft_strjoin("PWD=", tmp);
	if (m->pwd)
		free(m->pwd);
	m->pwd = ft_strjoin(tmp, "\0");
	free(tmp);
	if ((!m->g_mini_env[j] && j != -1) || !m->pwd)
		return (1);
	return (0);
}

int	k_cd_user(t_minishell *m, int j)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (m->g_mini_env[i])
	{
		if (!ft_strncmp(m->g_mini_env[i], "HOME=", 5))
		{
			if (j != -1)
				free(m->g_mini_env[j]);
			if (k_cd_user2(i, m, j) == 1)
				return (1);
			k = 1;
		}
		i++;
	}
	if (k == 0)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	return (0);
}

int	k_cd_dotdot(t_minishell *minishell, int j)
{
	char	*tmp;

	tmp = d_substr(minishell->pwd, 0, d_strlen(minishell->pwd)
			- d_strlen(ft_strrchr(minishell->pwd, '/')));
	if (!tmp)
		return (1);
	free (minishell->pwd);
	if (tmp[0] == '\0')
		minishell->pwd = d_strjoin(tmp, "/\0");
	else
		minishell->pwd = d_strjoin(tmp, "\0");
	if (!minishell->pwd)
		return (1);
	if (!d_strncmp("/", minishell->pwd, d_strlen(minishell->pwd)))
	{
		if (k_dotdot2(minishell, j) == 1)
			return (1);
	}
	if (j != -1)
	{
		free(minishell->g_mini_env[j]);
		minishell->g_mini_env[j] = ft_strjoin("PWD=", minishell->pwd);
	}
	return (0);
}

int	k_cd_dash2(int j)
{
	if (j != 0)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		free(g_error[0]);
		g_error[0] = d_calloc(2, sizeof(char));
		g_error[0][0] = '1';
		return (1);
	}
	return (0);
}

int	k_cd_dash(t_minishell *m, int j)
{
	int		i;

	i = -1;
	while (m->g_mini_env[++i])
	{
		if (!ft_strncmp(m->g_mini_env[i], "OLDPWD=", 7))
		{
			if (k_cd_dash_loop(j, m, i) == 1)
				return (1);
			j = 0;
		}
	}
	if (k_cd_dash2(j) == 1)
		return (1);
	return (0);
}
