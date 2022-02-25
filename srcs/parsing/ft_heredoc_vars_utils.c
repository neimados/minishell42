/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_vars_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:56:20 by dso               #+#    #+#             */
/*   Updated: 2022/02/21 11:59:33 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	d_skip_vars_hd(char *tmp, int i)
{
	while (tmp[i] && tmp[i] != '$')
			i++;
	return (i);
}

int	d_skip_vars3_hd(char *tmp, int i)
{
	while (tmp[i] && tmp[i] != '\'' && tmp[i] != '\"' && tmp[i] != ' ')
		i++;
	return (i);
}

int	d_skip_vars2_hd(char *tmp, int i)
{	
	i++;
	if (tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	if (tmp[i] == '?')
		i++;
	else
		i = d_skip_vars3_hd(tmp, i);
	return (i);
}
