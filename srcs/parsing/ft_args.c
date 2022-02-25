/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:42:37 by dso               #+#    #+#             */
/*   Updated: 2022/02/25 13:28:17 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_loop_args2(t_minishell *m, t_cmds *c, char *arg, t_parsing *p)
{
	int	end;

	end = p->end;
	p->start = p->i;
	while (arg[p->i] && arg[p->i] != '>' && arg[p->i] != '<')
		p->i += 1;
	if (p->in != 0)
	{
		end = d_args_in(arg, c, m, p);
		if (end == -1)
			return (-1);
		p->in = 0;
	}
	else if (p->out != 0)
	{
		end = d_args_out(arg, c, m, p);
		if (end == -1)
			return (-1);
		p->out = 0;
	}
	return (end);
}

static int	d_loop_args(t_minishell *m, t_cmds *c, char *arg, t_parsing *p)
{
	int	i;
	int	end;

	i = 0;
	end = p->end;
	while (arg[i])
	{
		if (arg[i] == '<' || arg[i] == '>')
		{
			if (arg[i] == '<')
				p->in += 1;
			else if (arg[i] == '>')
				p->out += 1;
			i++;
		}
		else
		{
			p->i = i;
			end = d_loop_args2(m, c, arg, p);
			i = p->i;
		}
	}
	return (end);
}

static int	d_args_return(char **args, t_cmds *c, int end)
{
	if (d_put_cmds(args, c) == 1)
		return (1);
	if (end == 1)
	{
		d_putstr_fd(c->infile, 2);
		d_putstr_fd(" : No such file or directory\n", 2);
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		g_error[0] = d_strdup("1");
	}
	return (0);
}

int	d_put_args(char **args, t_cmds *cmd, char *heredoc, t_minishell *mshell)
{
	int			i;
	t_parsing	p;

	i = 0;
	p.end = 0;
	p.in = 0;
	p.out = 0;
	p.tmp = heredoc;
	cmd->cmd = d_calloc((d_count_cmds(args) + 1), sizeof(char *));
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
	return (d_args_return(args, cmd, p.end));
}
