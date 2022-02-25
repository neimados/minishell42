/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:40:38 by dso               #+#    #+#             */
/*   Updated: 2022/02/21 11:57:34 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*d_loop_vars_hd(char *tmp, int i, char *str)
{
	int		start;
	char	*carry;

	start = i;
	while (tmp[i] && tmp[i] != '$')
			i++;
	carry = d_substr(tmp, start, i - start);
	if (!carry)
		return (NULL);
	str = d_strjoin(str, carry);
	free(carry);
	if (!str)
		return (NULL);
	return (str);
}

static char	*d_loop_vars3_hd(char *tmp, int i, t_minishell *mshell, char *str)
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

static char	*d_loop_vars2_hd(char *tmp, int i, char *str, t_minishell *mshell)
{
	char	*value;

	i++;
	if (tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	if (tmp[i] == '?')
	{
		value = d_var_err();
		if (!value)
			return (NULL);
		str = d_strjoin(str, value);
		if (!str)
			return (NULL);
		free(value);
		i++;
	}
	else
		str = d_loop_vars3_hd(tmp, i, mshell, str);
	return (str);
}

char	*d_check_vars2(char *tmp, t_minishell *mshell)
{
	char	*str;
	int		i;

	i = 0;
	str = d_calloc(1, sizeof(char));
	if (!str)
		return (NULL);
	while (tmp[i])
	{
		if (tmp[i] != '$')
		{
			str = d_loop_vars_hd(tmp, i, str);
			if (!str)
				return (NULL);
			i = d_skip_vars_hd(tmp, i);
		}
		else
		{
			str = d_loop_vars2_hd(tmp, i, str, mshell);
			if (!str)
				return (NULL);
			i = d_skip_vars2_hd(tmp, i);
		}
	}
	return (str);
}
