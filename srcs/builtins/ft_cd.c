/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:01:34 by dso               #+#    #+#             */
/*   Updated: 2022/02/28 19:39:34 by kmammeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	k_set_oldpwd(t_minishell *minishell, int j, char *old)
{
	int		i;

	i = -1;
	if (j == -1)
		return (0);
	while (minishell->g_mini_env[++i] && j != -1)
	{
		if (!d_strncmp(minishell->g_mini_env[i], "OLDPWD=", 7))
		{
			free(minishell->g_mini_env[i]);
			minishell->g_mini_env[i] = ft_strjoin("OLDPWD=", old);
			j = -2;
		}
	}
	if (j != -2)
	{
		if (j != -1)
		{
			if (k_cd_oldpwd(minishell, old) == 1)
				return (1);
		}
	}
	return (0);
}

int	k_chdir(t_minishell *minishell, char *pwd, char **tmp2, char **cmds)
{
	int	i;

	i = 0;
	if (chdir(minishell->pwd) == -1)
	{
		free(minishell->pwd);
		minishell->pwd = d_strdup(pwd);
		d_free_tab(minishell->g_mini_env);
		minishell->g_mini_env = d_calloc(d_count_tab(tmp2) + 1, sizeof(char *));
		if (!minishell->g_mini_env)
			return (1);
		while (tmp2[i])
		{
			minishell->g_mini_env[i] = d_strdup(tmp2[i]);
			if (!minishell->g_mini_env[i])
				return (1);
			i++;
		}
		k_error(cmds[1], strerror(errno));
		return (1);
	}
	return (0);
}

void	k_return_err(char *pwd, char *old, char **tmp2, t_minishell *m)
{
	if (m->pwd)
		free(m->pwd);
	m->pwd = old;
	if (m->g_mini_env)
		d_free_tab(m->g_mini_env);
	m->g_mini_env = tmp2;
	if (pwd)
		free(pwd);
	return ;
}

void	k_return_err2(char *pwd, char *old)
{
	if (pwd)
		free(pwd);
	free (old);
	return ;
}

void	ft_cd(char **cmds, t_minishell *minishell)
{
	char	*old;
	int		j;
	char	**tmp2;
	char	*pwd;

	old = d_strdup(minishell->pwd);
	if (!old)
		return ;
	pwd = d_strdup(minishell->pwd);
	if (!pwd)
		return (k_return_err2(pwd, old));
	j = k_search_pwd(minishell);
	tmp2 = k_cp_env(minishell);
	if (!tmp2)
		return (k_return_err2(pwd, old));
	if (k_cd_ignore(tmp2, cmds) == 1)
		return (k_return_err(pwd, old, tmp2, minishell));
	if (k_cd_type(minishell, cmds, j) == 1)
		return (k_return_err(pwd, old, tmp2, minishell));
	if (k_set_oldpwd(minishell, j, old) == 1)
		return (k_return_err(pwd, old, tmp2, minishell));
	if (k_chdir(minishell, pwd, tmp2, cmds) == 1)
		return (k_return_err(pwd, old, tmp2, minishell));
	k_free_end(old, tmp2, pwd);
}
