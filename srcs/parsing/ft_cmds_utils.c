/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:16:07 by dso               #+#    #+#             */
/*   Updated: 2022/03/01 13:02:49 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_loop_count_cmds2(char *arg, int i)
{
	if (arg[i] == '\'')
	{
		i++;
		while (arg[i] && arg[i] != '\'')
			i++;
		i++;
	}
	else if (arg[i] == '\"')
	{
		i++;
		while (arg[i] && arg[i] != '\"')
			i++;
		i++;
	}
	return (i);
}

static int	d_loop_count_cmds3(char *arg, int j)
{
	while (arg[j] && (arg[j] != '>' && arg[j] != '<'
			&& arg[j] != '\'' && arg[j] != '\"'))
		j++;
	return (j);
}

static int	d_loop_count_cmds(char *arg, int *sign, int j)
{
	int	count;

	count = 0;
	while (arg[j])
	{
		if (arg[j] == '\'' || arg[j] == '\"')
		{
			j = d_loop_count_cmds2(arg, j);
			count++;
		}
		else if (arg[j] == '>' || arg[j] == '<')
		{
			*sign += 1;
			j++;
		}
		else
		{
			if (*sign == 0)
				count++;
			else
				*sign = 0;
			j = d_loop_count_cmds3(arg, j);
		}
	}
	return (count);
}

int	d_count_cmds(char **args)
{
	int		i;
	int		j;
	int		sign;
	int		count;

	i = 0;
	j = 0;
	sign = 0;
	count = 0;
	while (args[i])
	{
		count += d_loop_count_cmds(args[i], &sign, j);
		i++;
	}
	return (count);
}

void	d_init_struct_parsing(t_parsing *p)
{
	p->i = 0;
	p->j = 0;
	p->k = 0;
	p->l = 0;
	p->sign = 0;
	p->sq = 0;
	p->dq = 0;
}
