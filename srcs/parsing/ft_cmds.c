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

static int	d_put_cmds2(char *arg, t_cmds *cmd, int *k, int *sign)
{
	int		j;
	int		sq;
	int		dq;
	char	*tmp;
	int		start;

	j = 0;
	sq = 0;
	dq = 0;
	start = 0;
	while (arg[j])
	{
		if (arg[j] == '\'' && dq % 2 == 0)
			sq++;
		else if (arg[j] == '\"' && sq % 2 == 0)
			dq++;
		else if ((arg[j] == '>' || arg[j] == '<')
			&& (sq % 2 == 0 && dq % 2 == 0))
		{
			*sign += 1;
			j++;
		}
		start = j;
		if (arg[j] == '\'' && sq % 2 != 0)
		{
			j++;
			while (arg[j] && arg[j] != '\'')
				j++;
			j++;
		}
		else if (arg[j] == '\"' && dq % 2 != 0)
		{
			j++;
			while (arg[j] && arg[j] != '\"')
				j++;
			j++;
		}
		while (arg[j] && arg[j] != '>' && arg[j] != '<')
			j++;
		if (*sign == 0)
		{
			tmp = d_substr(arg, start, j - start);
			if (!tmp)
				return (-1);
			cmd->cmd[*k] = d_write_cmd_trim(tmp);
			if (!cmd->cmd[*k])
				return (-1);
			*k += 1;
			*sign = 0;
		}
	}
	return (0);
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
		if (d_put_cmds2(args[i], cmd, &k, &sign) == -1)
			return (1);
		i++;
	}
	return (0);
}
