/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:42:37 by dso               #+#    #+#             */
/*   Updated: 2022/03/03 11:35:04 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_loop_args2_loop(char *arg, int i)
{
	while (arg[i] && arg[i] != '<' && arg[i] != '>')
			i++;
	return (i);
}

static int	d_loop_args2(t_minishell *m, t_cmds *c, char *arg, t_parsing *p)
{
	int	end;

	end = p->end;
	p->start = p->i;
	if (p->in != 0)
	{
		p->i = d_loop_args2_loop(arg, p->i);
		end = d_args_in(arg, c, m, p);
		if (end == -1)
			return (-1);
		p->in = 0;
	}
	else if (p->out != 0)
	{
		p->i = d_loop_args2_loop(arg, p->i);
		end = d_args_out(arg, c, m, p);
		if (end == -1)
			return (-1);
		p->out = 0;
	}
	else
		while (arg[p->i] && arg[p->i] != '>' && arg[p->i] != '<'
			&& arg[p->i] != '\'' && arg[p->i] != '\"')
			p->i += 1;
	return (end);
}

static int	d_loop_args(t_minishell *m, t_cmds *c, char *a, t_parsing *p)
{
	int	i;
	int	end;

	i = 0;
	end = p->end;
	while (a[i])
	{
		if ((a[i] == '\'' || a[i] == '\"') && (p->in == 0 && p->out == 0))
			i = d_loop_args_quotes(a, i);
		else if ((a[i] == '<' || a[i] == '>') && (p->in == 0 && p->out == 0))
		{
			if (a[i] == '<')
				p->in += 1;
			else if (a[i] == '>')
				p->out += 1;
			i++;
		}
		else
		{
			p->i = i;
			end = d_loop_args2(m, c, a, p);
			i = p->i;
		}
	}
	return (end);
}

static int	d_args_return(char **args, t_cmds *c)
{
	if (d_put_cmds(args, c) == 1)
		return (1);
	return (0);
}

int	d_put_args(char **args, t_cmds *cmd, char *heredoc, t_minishell *mshell)
{
	int			i;
	int			length;
	t_parsing	p;

	i = 0;
	p.end = 0;
	p.in = 0;
	p.out = 0;
	length = d_count_cmds(args);
	printf("LENGTH %d\n", length);
	p.tmp = heredoc;
	cmd->cmd = d_calloc((length + 1), sizeof(char *));
	cmd->cmd[0] = NULL;
	if (!cmd->cmd)
		return (1);
	while (args[i])
	{
		p.start = 0;
		p.end = d_loop_args(mshell, cmd, args[i], &p);
		if (p.end == -1)
			return (1);
		i++;
	}
	return (d_args_return(args, cmd));
}
