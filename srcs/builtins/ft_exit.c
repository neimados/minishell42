/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/03/01 11:01:11 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_check_digit(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '-')
		i++;
	while (cmd[i])
	{
		if ((cmd[i] < '0' || cmd[i] > '9') && cmd[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static void	d_loop_free_exit(t_minishell *mshell)
{
	t_cmds	*test;

	test = mshell->cmds;
	while (test != NULL)
	{
		d_free_tab(test->cmd);
		if (test->infile)
			free(test->infile);
		else if (test->outfile)
			free(test->outfile);
		test = test->next;
		free(mshell->cmds);
		mshell->cmds = test;
	}
}

static void	d_exit_free(t_minishell *mshell, int key)
{
	d_loop_free_exit(mshell);
	if (key == 0)
		printf("\b\bexit\n");
	free(mshell->pwd);
	d_free_tab(mshell->g_mini_env);
	free(mshell);
	d_free_tab(g_error);
}

static int	d_exit_arg(char *cmd)
{
	unsigned char	error;

	error = 0;
	if (d_check_digit(cmd) == 1)
	{
		d_putstr_fd("exit: ", 2);
		d_putstr_fd(cmd, 2);
		d_putstr_fd(": numeric argument required\n", 2);
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		g_error[0] = d_strdup("255");
		error = 255;
	}
	else
	{
		error = d_atoi(cmd);
		if (error)
			while (error > 255)
				error = error - 256;
	}
	return (error);
}

void	ft_exit(t_minishell *mshell, char **cmds, int key)
{
	unsigned char	error;

	error = d_atoi(g_error[0]);
	if (d_count_tab(cmds) > 2)
	{
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		g_error[0] = d_strdup("1");
		if (d_check_digit(cmds[1]) == 0)
		{
			d_putstr_fd("exit\nexit: too many arguments\n", 2);
			return ;
		}
	}
	if (cmds[1])
		error = d_exit_arg(cmds[1]);
	d_exit_free(mshell, key);
	exit(error);
}
