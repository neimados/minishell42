/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:32:08 by dso               #+#    #+#             */
/*   Updated: 2022/02/28 20:04:51 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	d_loop_print_declare(char *line)
{
	int	i;

	i = 0;
	printf("declare -x ");
	if (d_check_export(line) == 1)
	{
		while (line[i] != '=')
		{
			printf("%c", line[i]);
			i++;
		}
		printf("%c\"", line[i]);
		i++;
		while (line[i])
		{
			printf("%c", line[i]);
			i++;
		}
		printf("\"\n");
	}
	else
		printf("declare -x %s\n", line);
}

void	d_print_declare_export(t_minishell *mshell)
{
	int	i;
	int	exist;

	i = -1;
	exist = 0;
	while (mshell->g_mini_env[++i])
	{
		if (mshell->g_mini_env[i][0] == 'O' && mshell->g_mini_env[i][1] == 'L'
		&& mshell->g_mini_env[i][2] == 'D' && mshell->g_mini_env[i][3] == 'P'
		&& mshell->g_mini_env[i][4] == 'W' && mshell->g_mini_env[i][5] == 'D'
		&& mshell->g_mini_env[i][6] == '=')
			exist = 1;
	}
	i = -1;
	while (mshell->g_mini_env[++i])
		d_loop_print_declare(mshell->g_mini_env[i]);
	if (exist == 0)
		printf("declare -x OLDPWD\n");
	return ;
}

int	d_check_export(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
