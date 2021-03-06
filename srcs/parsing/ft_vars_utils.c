/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:56:43 by dso               #+#    #+#             */
/*   Updated: 2022/02/28 19:48:57 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	d_check_path_length(char *env, int i)
{
	int	count;

	count = 0;
	while (env[i])
	{
		if (env[i] == '>' || env[i] == '<')
		{
			count += 3;
			i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count + 1);
}

static char	*d_check_path_fill(char *env, int i)
{
	char	*value;
	int		j;

	j = -1;
	value = d_calloc(d_check_path_length(env, i), sizeof(char));
	while (env[i])
	{
		if (env[i] == '>' || env[i] == '<')
		{
			value[++j] = '\'';
			value[++j] = env[i];
			value[++j] = '\'';
		}
		else
			value[++j] = env[i];
		i++;
	}
	return (value);
}

char	*d_check_path(char *variable, char *env)
{
	int		i;
	char	*value;

	i = 0;
	while (variable[i])
	{
		if (variable[i] != env[i])
			return (NULL);
		i++;
	}
	if (env[i] != '=')
		return (NULL);
	i++;
	value = d_check_path_fill(env, i);
	return (value);
}

char	*d_loop_vars3(char *tmp, int i, t_minishell *mshell, char *str)
{
	int		start;
	char	*variable;
	char	*value;
	int		j;

	start = i;
	j = 0;
	while (tmp[i] && tmp[i] != '\'' && tmp[i] != '\"' && tmp[i] != ' ')
		i++;
	variable = d_substr(tmp, start, i - start);
	while (mshell->g_mini_env[j])
	{
		if (variable[0] == mshell->g_mini_env[j][0])
		{
			value = d_check_path(variable, mshell->g_mini_env[j]);
			if (value)
			{
				str = d_strjoin(str, value);
				free(value);
			}
		}
	j++;
	}
	free(variable);
	return (str);
}
