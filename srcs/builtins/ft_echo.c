/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:00:43 by dso               #+#    #+#             */
/*   Updated: 2022/02/25 18:08:57 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	d_loop_echo(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '\'' && cmd[i] != '\"')
			printf("%c", cmd[i]);
		i++;
	}
}

static int	d_echo_n(char **cmds)
{
	if (cmds[1][0] == '-' && cmds[1][1] == 'n')
		return (1);
	return (0);
}

static void	d_check_echo(void)
{
	printf("\n");
	exit(EXIT_SUCCESS);
}

void	ft_echo(char **cmds)
{
	int	i;
	int	n;
	int	size;

	i = 1;
	if (!cmds[1])
		d_check_echo();
	n = d_echo_n(cmds);
	size = d_count_tab(cmds);
	if (size == 1)
		exit(EXIT_SUCCESS);
	if (n == 1)
		i = 2;
	while (cmds[i])
	{
		d_loop_echo(cmds[i]);
		i++;
		if (i < size)
			printf(" ");
	}
	if (n == 0)
		printf("\n");
	exit(EXIT_SUCCESS);
}
