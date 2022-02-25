/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:29:38 by kmammeri          #+#    #+#             */
/*   Updated: 2022/02/23 17:46:03 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	k_dotdot2(t_minishell *minishell, int j)
{
	free(minishell->pwd);
	free(minishell->g_mini_env[j]);
	minishell->pwd = ft_strdup("/");
	minishell->g_mini_env[j] = ft_strdup("PWD=/");
	if (!minishell->pwd || !minishell->g_mini_env[j])
		return (1);
	return (0);
}

void	k_free_end(char *old, char **tmp2, char *pwd)
{
	if (old)
		free (old);
	if (tmp2)
		d_free_tab(tmp2);
	if (pwd)
		free (pwd);
	return ;
}

int	k_cd_oldpwd(t_minishell *minishell, char *old)
{
	char	*oldjoin;
	char	**oldsplit;

	oldjoin = ft_strjoin("export OLDPWD=", old);
	oldsplit = ft_split(oldjoin, ' ');
	if (!oldsplit)
		return (1);
	ft_export(oldsplit, minishell);
	k_free_oldpwd(oldsplit, oldjoin);
	return (0);
}

int	k_cd_dash_loop(int j, t_minishell *m, int i)
{
	char	*tmp;

	if (j != -1)
		free(m->g_mini_env[j]);
	tmp = d_substr(m->g_mini_env[i], 7, d_strlen(m->g_mini_env[i] + 7));
	if (!tmp)
		return (1);
	if (j != -1)
		m->g_mini_env[j] = ft_strjoin("PWD=", tmp);
	free(m->pwd);
	m->pwd = ft_strjoin(tmp, "\0");
	if (!m->pwd)
		return (1);
	printf("%s\n", m->pwd);
	free (tmp);
	return (0);
}
