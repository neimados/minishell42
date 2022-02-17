/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:57:09 by dso               #+#    #+#             */
/*   Updated: 2022/02/16 15:55:11 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	d_pipe_error(char **tmp, t_cmds *cmd)
{
	d_free_tab(tmp);
	d_free_tab(cmd->cmd);
	free(cmd);
	return (1);
}

int	d_pipe_error2(char **args, char *heredoc)
{
	d_free_tab(args);
	unlink(heredoc);
	free(heredoc);
	return (1);
}

int	d_pipe_return(char **tmp, char *input)
{
	d_free_tab(tmp);
	free(input);
	return (0);
}
