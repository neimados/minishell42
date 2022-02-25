/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:29:41 by dso               #+#    #+#             */
/*   Updated: 2022/02/23 12:40:38 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	k_free_oldpwd(char **oldsplit, char *oldjoin)
{
	d_free_tab(oldsplit);
	free(oldjoin);
}

void	k_error(char *str1, char *str2)
{
	if (str1[0])
		write(2, "minishell: cd: ", 15);
	write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, ": ", 2);
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	return ;
}

int	ft_strncmp(const char *first, const char *second, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (0);
	while (i < len - 1 && first[i] == second[i] && first[i])
		i++;
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}

char	**k_cp_env(t_minishell *minishell)
{
	char	**tmp2;
	int		i;

	i = 0;
	tmp2 = malloc(sizeof(char *) * (d_count_tab(minishell->g_mini_env) + 1));
	if (!tmp2)
		return (NULL);
	while (minishell->g_mini_env[i])
	{
		tmp2[i] = ft_strdup(minishell->g_mini_env[i]);
		i++;
	}
	tmp2[i] = NULL;
	return (tmp2);
}

int	k_search_pwd(t_minishell *m)
{
	int	i;

	i = 0;
	while (m->g_mini_env[i])
	{
		if (m->g_mini_env[i][0] == 'P' && m->g_mini_env[i][1] == 'W'
		&& m->g_mini_env[i][2] == 'D' && m->g_mini_env[i][3] == '=')
			return (i);
		i++;
	}
	return (-1);
}
