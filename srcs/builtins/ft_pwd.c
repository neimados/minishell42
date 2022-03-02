/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/28 21:17:15 by kmammeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char **cmds, t_minishell *mshell)
{
	(void)cmds;
	printf("%s\n", mshell->pwd);
	exit(EXIT_SUCCESS);
}

int	k_cd_others2(char *tmp, char **cmds, t_minishell *minishell)
{
	free(minishell->pwd);
	if (cmds[1][ft_strlen(cmds[1]) - 1] == '/' && ft_strlen(cmds[1]) != 1)
	{
		tmp = d_strjoin(tmp, cmds[1]);
		if (!tmp)
			return (1);
		minishell->pwd = d_substr(tmp, 0, d_strlen(tmp) - 1);
	}
	else
		minishell->pwd = ft_strjoin(tmp, cmds[1]);
	free(tmp);
	if (!minishell->pwd)
		return (1);
	return (0);
}
