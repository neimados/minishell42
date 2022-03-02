/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/03/01 12:11:46 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*d_write_cmd(char *arg, t_parsing *p, t_cmds *c)
{
	int		j;
	int		k;
	char	*tmp;

	j = p->j;
	k = p->k;
	tmp = d_substr(arg, 0, j);
	if (!tmp)
		return (NULL);
	c->cmd[k] = d_write_cmd_trim(tmp);
	if (!c->cmd[k])
		return (NULL);
	return (c->cmd[k]);
}

static int	d_skip_cmds(t_parsing *p, char *arg)
{
	int	j;
	int	sq;
	int	dq;

	j = p->j;
	sq = 0;
	dq = 0;
	while (arg[j])
	{
		if (arg[j] == '\'' && dq % 2 == 0)
			sq++;
		else if (arg[j] == '\"' && sq % 2 == 0)
			dq++;
		if ((arg[j] == '>' || arg[j] == '<') && (sq % 2 == 0 && dq % 2 == 0))
			return (j);
		j++;
	}
	return (j);
}

static int	d_loop_put_cmds(t_parsing *p, char *arg, t_cmds *c, int sign)
{
	t_parsing	pp;
	int			k;

	pp.j = p->j;
	pp.k = p->k;
	k = p->k;
	if (sign == 0)
	{
		c->cmd[k] = d_write_cmd(arg, &pp, c);
		if (!c->cmd[k])
			return (-1);
	}
	return (0);
}

static int	d_put_cmds2(char *arg, t_cmds *cmd, int k, int sign)
{
	t_parsing	p;

	d_init_struct_parsing(&p);
	p.k = k;
	while (arg[p.j])
	{
		if (arg[p.j] == '\'' && p.dq % 2 == 0)
			p.sq += 1;
		else if (arg[p.j] == '\"' && p.sq % 2 == 0)
			p.dq += 1;
		if ((arg[p.j] == '>' || arg[p.j] == '<')
			&& (p.sq % 2 == 0 && p.dq % 2 == 0))
		{
			sign = 1;
			p.j += 1;
		}
		else
		{
			p.j = d_skip_cmds(&p, arg);
			p.k = d_loop_put_cmds(&p, arg, cmd, sign);
			return (d_put_cmds2_else(sign, p.k));
		}
	}
	return (sign);
}

int	d_put_cmds(char **args, t_cmds *cmd)
{
	int	i;
	int	k;
	int	sign;

	i = 0;
	k = 0;
	sign = 0;
	while (args[i])
	{
		sign = d_put_cmds2(args[i], cmd, k, sign);
		if (sign == -1)
			return (1);
		else if (sign > 1)
		{
			if (sign == 3)
				k++;
			sign = 0;
		}
		i++;
	}
	return (0);
}
