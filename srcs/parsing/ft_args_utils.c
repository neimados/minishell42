/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:42:32 by dso               #+#    #+#             */
/*   Updated: 2022/02/28 16:25:01 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	d_args_out2(t_cmds *cmd, char *tmp)
{
	if (!tmp)
		return (1);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = tmp;
	if (!cmd->outfile)
		return (1);
	return (0);
}

int	d_args_out(char *arg, t_cmds *cmd, t_minishell *mshell, t_parsing *p)
{
	char	*tmp;
	int		end;

	(void)mshell;
	end = p->end;
	if (p->end != 0)
		return (1);
	tmp = d_substr(arg, p->start, p->i - p->start);
	if (d_args_out2(cmd, tmp) == 1)
		return (-1);
	if (p->out == 1)
	{
		cmd->type = 1;
		p->fd = open(cmd->outfile, O_RDWR | O_TRUNC | O_CREAT, 0777);
	}
	else if (p->out == 2)
	{
		cmd->type = 2;
		p->fd = open(cmd->outfile, O_RDWR | O_APPEND | O_CREAT, 0777);
	}
	if (p->fd == -1)
		end = 1;
	close(p->fd);
	return (end);
}

int	d_args_heredoc(char *arg, t_minishell *mshell, t_cmds *cmd, t_parsing *p)
{
	char	*hd_stop;

	hd_stop = d_substr(arg, p->start, p->i - p->start);
	if (!hd_stop)
		return (1);
	if (d_start_heredoc(hd_stop, p->tmp, mshell) == 1)
		return (1);
	if (p->end == 0)
	{
		cmd->heredoc = 1;
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = d_strdup(p->tmp);
		if (!cmd->infile)
			return (1);
	}
	return (0);
}

int	d_args_in(char *arg, t_cmds *cmd, t_minishell *mshell, t_parsing *p)
{
	char	*tmp;
	int		end;

	end = p->end;
	if (p->in == 1 && p->end == 0)
	{
		tmp = d_substr(arg, p->start, p->i - p->start);
		if (!tmp)
			return (-1);
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = tmp;
		p->fd = open(cmd->infile, O_RDONLY);
		if (p->fd == -1)
			end = 1;
		close(p->fd);
	}
	else if (p->in == 2)
	{
		if (d_args_heredoc(arg, mshell, cmd, p) == 1)
			return (-1);
	}
	return (end);
}
