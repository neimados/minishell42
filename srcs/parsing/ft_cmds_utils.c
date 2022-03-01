/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:16:07 by dso               #+#    #+#             */
/*   Updated: 2022/02/28 19:22:16 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_loop_count_cmds(char *arg)
{
	int	sign;
	int	count;
	int	i;

	sign = 0;
	count = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '>' || arg[i] == '<')
		{
			sign++;
			i++;
		}
		else
		{
			if (sign == 0)
				count++;
			else
				sign = 0;
			while (arg[i] && (arg[i] != '>' && arg[i] != '<'))
				i++;
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
		count += d_loop_count_cmds(args[i]);
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
