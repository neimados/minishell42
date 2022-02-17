/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:54:24 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 18:10:19 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*d_shlvl_return(t_minishell *mshell, int shlvl)
{
	char	*tmp;
	char	*nb;

	tmp = d_strdup("SHLVL=");
	if (!tmp)
		d_cp_env_err(mshell);
	nb = d_itoa(shlvl + 1);
	tmp = d_strjoin(tmp, nb);
	free(nb);
	return (tmp);
}

static char	*d_write_shlvl(t_minishell *mshell, char *env)
{
	char	*tmp;
	int		length;
	int		shlvl;

	shlvl = 0;
	length = d_strlen(env);
	if (length != 6)
	{
		tmp = d_substr(env, 6, (length - 6));
		if (!tmp)
			d_cp_env_err(mshell);
		shlvl = d_atoi(tmp);
		free(tmp);
		if (shlvl > 999)
		{
			d_putstr_fd("warning: shell level too high, resetting to 1\n", 2);
			shlvl = 0;
		}
		else if (shlvl == 999)
		{
			tmp = d_strdup("SHLVL=");
			return (tmp);
		}
	}
	return (d_shlvl_return(mshell, shlvl));
}

static void	d_replace_lvl(t_minishell *mshell, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (envp[i])
	{
		if (envp[i][0] == 'O' && envp[i][1] == 'L' && envp[i][2] == 'D'
		&& envp[i][3] == 'P' && envp[i][4] == 'W' && envp[i][5] == 'D'
		&& envp[i][6] == '=')
			i++;
		else
		{
			if (envp[i][0] == 'S' && envp[i][1] == 'H' && envp[i][2] == 'L'
			&& envp[i][3] == 'V' && envp[i][4] == 'L' && envp[i][5] == '=')
				mshell->g_mini_env[++j] = d_write_shlvl(mshell, envp[i]);
			else
			{
				mshell->g_mini_env[++j] = d_strdup(envp[i]);
			}
			if (!mshell->g_mini_env[j])
				d_cp_env_err(mshell);
			i++;
		}
	}
}

static void	d_create_lvl(t_minishell *mshell, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'O' && envp[i][1] == 'L' && envp[i][2] == 'D'
		&& envp[i][3] == 'P' && envp[i][4] == 'W' && envp[i][5] == 'D'
		&& envp[i][6] == '=')
			i++;
		else
		{
			mshell->g_mini_env[j] = d_strdup(envp[i]);
			if (!mshell->g_mini_env[j])
				d_cp_env_err(mshell);
		}
		i++;
		j++;
	}
	mshell->g_mini_env[j] = d_strdup("SHLVL=1");
}

void	ft_cp_env(char **envp, t_minishell *mshell)
{
	int	lvl;
	int	length;

	lvl = d_search_shlvl(envp);
	length = ft_chr_old(envp);
	d_search_pwd(mshell);
	if (lvl == 0)
	{
		mshell->g_mini_env = malloc(sizeof(char *) * (length + 2));
		if (!mshell->g_mini_env)
			d_cp_env_err(mshell);
		d_create_lvl(mshell, envp);
		mshell->g_mini_env[length + 1] = 0;
	}
	else
	{
		mshell->g_mini_env = malloc(sizeof(char *) * (length + 1));
		if (!mshell->g_mini_env)
			d_cp_env_err(mshell);
		d_replace_lvl(mshell, envp);
		mshell->g_mini_env[length] = 0;
	}
}
