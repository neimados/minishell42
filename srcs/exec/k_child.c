/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_child.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:49:50 by dso               #+#    #+#             */
/*   Updated: 2022/03/02 18:28:29 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	k_child_dup(t_cmds *tmp, int in, int out)
{
	if (tmp->infile)
	{
		in = open(tmp->infile, O_RDONLY);
		if (in == -1)
			k_child_error_exit(tmp);
		if (dup2(in, STDIN_FILENO) == -1)
			ft_error(strerror(errno), NULL);
		close(in);
	}
	if (tmp->outfile)
	{
		if (tmp->type == 1)
		{
			out = open(tmp->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (dup2(out, STDOUT_FILENO) == -1)
				ft_error(strerror(errno), NULL);
		}
		else if (tmp->type == 2)
		{
			out = open(tmp->outfile, O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (dup2(out, STDOUT_FILENO) == -1)
				ft_error(strerror(errno), NULL);
		}
		close(out);
	}
}

void	k_child_infile(t_cmds *tmp, int i)
{
	int	fd_in;

	if (tmp->infile)
	{
		close(tmp->pipe[0]);
		fd_in = open(tmp->infile, O_RDONLY);
		if (fd_in == -1)
		{
			k_set_gerror();
			ft_error(tmp->infile, strerror(errno));
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_error(strerror(errno), NULL);
		close(fd_in);
	}
	else if (i != 0)
	{
		close (tmp->pipe[1]);
		fd_in = tmp->pipe[0];
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_error(strerror(errno), NULL);
		close(fd_in);
	}
}

void	k_child_outfile(t_cmds	*tmp)
{
	int	fd_out;

	if (tmp->outfile)
	{
		if (tmp->next)
			close(tmp->next->pipe[0]);
		if (tmp->type == 1)
		{
			fd_out = open(tmp->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (dup2(fd_out, STDOUT_FILENO) == -1)
				ft_error(strerror(errno), NULL);
		}
		else if (tmp->type == 2)
		{
			fd_out = open(tmp->outfile, O_WRONLY | O_APPEND
					| O_CREAT, 0666);
			if (dup2(fd_out, STDOUT_FILENO) == -1)
				ft_error(strerror(errno), NULL);
		}
	}
}

void	k_child_main(t_cmds	*tmp, t_minishell *minishell, int i)
{
	if (tmp)
	{
		k_child_infile(tmp, i);
		k_child_outfile(tmp);
		if (tmp->next)
		{
			while (tmp->next && tmp->next->pipe[1] < 0)
				tmp = tmp->next;
			if (tmp->next && tmp->cmd[0] && tmp->next->pipe[1] > 1)
			{
				if (dup2(tmp->next->pipe[1], STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL);
				close(tmp->next->pipe[1]);
			}
		}
		if (tmp->cmd[0])
			k_is_builtin_fct(tmp->cmd, minishell);
		else
			exit (0);
	}
}

void	k_child(t_minishell *minishell, int i)
{
	t_cmds	*tmp;
	t_cmds	*tmp2;

	tmp = minishell->cmds;
	if (i == 0)
		k_child_fd(tmp, minishell);
	tmp = k_child_close_pipe(i, tmp);
	tmp2 = tmp;
	tmp = tmp->next;
	k_child_main(tmp, minishell, i);
}
