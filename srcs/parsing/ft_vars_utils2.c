/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:56:43 by dso               #+#    #+#             */
/*   Updated: 2022/02/28 19:48:57 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	d_skip_vars3(char *tmp, int i)
{
	while (tmp[i] && tmp[i] != '\'' && tmp[i] != '\"' && tmp[i] != ' ')
		i++;
	return (i);
}

int	d_loop_vars_if(char *tmp, int i)
{
	i++;
	while (tmp[i] && tmp[i] != '\'')
		i++;
	if (tmp[i])
		i++;
	return (i);
}

char	*d_var_err(void)
{
	char	*var;

	var = d_strdup(g_error[0]);
	return (var);
}
