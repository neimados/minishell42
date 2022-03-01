/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:32:08 by dso               #+#    #+#             */
/*   Updated: 2022/02/28 20:04:51 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_export_quotes_len2(char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	return (i);
}

static int	d_export_quotes_len(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = d_export_quotes_len2(str, i);
			count += (i - 2);
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

static char	*d_export_quotes_loop(char *str, int length, int i, int j)
{
	char	*new;

	new = d_calloc(length, sizeof(char));
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				new[++j] = str[i++];
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				new[++j] = str[i++];
		}
		else
			new[++j] = str[i];
		i++;
	}
	return (new);
}

char	*d_export_quotes(char *str)
{
	int		length;
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = -1;
	length = d_export_quotes_len(str) + 1;
	new = d_export_quotes_loop(str, length, i, j);
	if (!new)
		return (NULL);
	return (new);
}
