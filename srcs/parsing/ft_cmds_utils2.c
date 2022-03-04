/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:16:07 by dso               #+#    #+#             */
/*   Updated: 2022/03/01 13:02:49 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_write_count_cmd_loop(char *tmp, int i, int *count)
{
	if (tmp[i] == '\'')
	{
		i++;
		while (tmp[i] && tmp[i] != '\'')
		{
			i++;
			*count += 1;
		}
	}
	else if (tmp[i] == '\"')
	{
		i++;
		while (tmp[i] && tmp[i] != '\"')
		{
			i++;
			*count += 1;
		}
	}
	return (i);
}

static int	d_write_count_cmd(char *tmp)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			i = d_write_count_cmd_loop(tmp, i, &count);
		else
			count++;
		i++;
	}
	return (count + 1);
}

static void	d_write_cmd_trim_loop(char *tmp, char *new, int *i, int *j)
{
	if (tmp[*i] == '\'')
	{
		*i += 1;
		while (tmp[*i] && tmp[*i] != '\'')
		{
			new[*j] = tmp[*i];
			*j += 1;
			*i += 1;
		}
	}
	else if (tmp[*i] == '\"')
	{
		*i += 1;
		while (tmp[*i] && tmp[*i] != '\"')
		{
			new[*j] = tmp[*i];
			*j += 1;
			*i += 1;
		}
	}
}

char	*d_write_cmd_trim(char *tmp)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = d_calloc(d_write_count_cmd(tmp), sizeof(char));
	if (!new)
		return (NULL);
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			d_write_cmd_trim_loop(tmp, new, &i, &j);
		else
		{
			new[j] = tmp[i];
			j++;
		}
		i++;
	}
	free(tmp);
	return (new);
}

int	d_put_cmds2_else(int sign, int k)
{
	if (k == -1)
		return (-1);
	if (sign == 0)
		return (3);
	return (2);
}
