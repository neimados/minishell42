/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:29:51 by dso               #+#    #+#             */
/*   Updated: 2022/02/08 12:58:50 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	d_loop_print_declare(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '=')
	{
		printf("%c", line[i]);
		i++;
	}
	printf("%c\"", line[i]);
	i++;
	while (line[i])
	{
		printf("%c", line[i]);
		i++;
	}
	printf("\"\n");
}
