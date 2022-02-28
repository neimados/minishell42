/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_exec_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:59:19 by dso               #+#    #+#             */
/*   Updated: 2022/02/28 15:08:38 by kmammeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *str1, char *str2)
{
	write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	if (str2)
	{
		write(2, ": ", 2);
		write(2, str2, ft_strlen(str2));
	}
	write(2, "\n", 1);
	if (!d_strncmp(g_error[0], "127", 3))
		exit(127);
	if (!d_strncmp(g_error[0], "1", 1))
		exit(1);
	else
		exit(errno);
}

int	k_loop_forks_check(int nbcmd, t_minishell *m, t_cmds *tmp, int i)
{
	if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "exit", i))
	{
		ft_exit(m, tmp->cmd, 0);
		return (1);
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "export", i))
	{
		ft_export(tmp->cmd, m);
		return (1);
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "cd", i))
	{
		ft_cd(tmp->cmd, m);
		return (1);
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "unset", i))
	{
		ft_unset(tmp->cmd, m);
		return (1);
	}
	return (0);
}

void	k_set_signals(int nbcmd, t_cmds *tmp, int i)
{
	d_free_tab(g_error);
	g_error = d_calloc(3, sizeof(char *));
	if (!g_error)
		return ;
	g_error[0] = d_strdup("0");
	if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "cat", i))
	{
		ft_terminal(2);
		signal(SIGINT, sigint_handler_spec);
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "./minishell", i))
	{
		ft_terminal(0);
		signal(SIGINT, sigint_handler_minishell);
	}
	else
	{
		ft_terminal(1);
		signal(SIGINT, sigint_handler_child);
	}
}

int	k_create_forks(int nbcmd, t_cmds *tmp, t_minishell *minishell, pid_t *forks)
{
	int		i;

	i = 0;
	while (i < nbcmd)
	{
		if (tmp->cmd)
		{
			if (tmp->next)
			{
				if (pipe(tmp->next->pipe) == -1)
					return (1);
			}
			forks[i] = fork();
			if (forks[i] == 0)
			{
				if (tmp->next && !tmp->next->next)
					close(tmp->next->pipe[0]);
				k_child(minishell, i);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	k_forks_end(int i, t_minishell *m, t_cmds *tmp2, pid_t *forks)
{
	int	j;
	int	stat[1];

	j = i;
	tmp2 = m->cmds->next;
	while (tmp2)
	{
		close(tmp2->pipe[0]);
		close(tmp2->pipe[1]);
		tmp2 = tmp2->next;
	}
	while (i >= 0)
	{
		waitpid(forks[i], stat, 0);
		if (i == j)
		{
			if (d_strncmp(g_error[0], "130", 3) != 0
				&& WEXITSTATUS(stat[0]) != 2)
			{
				free(g_error[0]);
				g_error[0] = d_itoa(WEXITSTATUS(stat[0]));
			}
		}
		i--;
	}
}
