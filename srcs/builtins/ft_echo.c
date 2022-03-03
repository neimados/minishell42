/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:00:43 by dso               #+#    #+#             */
/*   Updated: 2022/03/03 10:20:22 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	d_loop_echo(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("%c", cmd[i]);
		i++;
	}
}

static int	d_echo_n(char **cmds)
{
	int	i;
	int	j;

	i = 1;
	while (cmds[i])
	{
		j = 1;
		while (cmds[i][0] == '-' && cmds[i][j] == 'n')
			j++;
		if (cmds[i][j] != '\0' || d_strlen(cmds[i]) == 1)
			return (i);
		i++;
	}
	return (i);
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
	i = d_echo_n(cmds);
	n = i;
	size = d_count_tab(cmds);
	if (size == 1)
		exit(EXIT_SUCCESS);
	while (cmds[i])
	{
		d_loop_echo(cmds[i]);
		i++;
		if (i < size)
			printf(" ");
	}
	if (n <= 1)
		printf("\n");
	exit(EXIT_SUCCESS);
}
