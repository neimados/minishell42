/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:54:24 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 18:10:19 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	d_cp_env_err(t_minishell *mshell)
{
	d_free_tab(mshell->g_mini_env);
	write(2, "Malloc Error\n", 13);
	exit(EXIT_FAILURE);
}

int	d_search_shlvl(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'S' && envp[i][1] == 'H' && envp[i][2] == 'L'
		&& envp[i][3] == 'V' && envp[i][4] == 'L' && envp[i][5] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_chr_old(char **envp)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'O' && envp[i][1] == 'L' && envp[i][2] == 'D'
		&& envp[i][3] == 'P' && envp[i][4] == 'W' && envp[i][5] == 'D'
		&& envp[i][6] == '=')
			count--;
		count++;
		i++;
	}
	return (count);
}

void	d_search_pwd(t_minishell *mshell)
{
	int		i;
	char	*buffer;

	i = 1;
	buffer = d_calloc(i, sizeof(char));
	if (!buffer)
		return ;
	while (buffer == NULL || buffer[0] == '\0')
	{
		free(buffer);
		buffer = d_calloc(i, sizeof(char));
		if (!buffer)
			exit(EXIT_FAILURE);
		getcwd(buffer, i);
		i++;
	}
	mshell->pwd = buffer;
}
