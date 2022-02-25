/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/22 14:53:18 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_check_env_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(char **cmds, t_minishell *mshell)
{
	int	i;

	i = 0;
	if (cmds[1])
	{
		printf("env: %s: No such file or directory\n", cmds[1]);
		exit(EXIT_FAILURE);
	}
	d_replace_underscore(mshell);
	while (mshell->g_mini_env[i])
	{
		if (d_check_env_line(mshell->g_mini_env[i]) == 1)
			printf("%s\n", mshell->g_mini_env[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
