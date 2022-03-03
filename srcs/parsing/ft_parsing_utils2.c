/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:24:01 by dso               #+#    #+#             */
/*   Updated: 2022/03/03 11:27:37 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	d_check_quotes_loop(char *input, int i, t_minishell *mshell)
{
	if (input[i] == '\'')
	{
		mshell->nb_sq += 1;
		i++;
		while (input[i] && input[i] != '\'')
			i++;
		if (input[i] == '\'')
		{
			mshell->nb_sq += 1;
			i++;
		}
	}
	else if (input[i] == '\"')
	{
		mshell->nb_dq += 1;
		i++;
		while (input[i] && input[i] != '\"')
			i++;
		if (input[i] == '\"')
		{
			mshell->nb_dq += 1;
			i++;
		}
	}
	return (i);
}
