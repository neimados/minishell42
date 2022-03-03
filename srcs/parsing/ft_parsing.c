/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:57:09 by dso               #+#    #+#             */
/*   Updated: 2022/03/03 11:31:45 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_parsing_args(t_minishell *mshell, t_cmds *cmd, char *tmp, int i)
{
	char	**args;
	char	*heredoc;

	args = d_split(tmp, ' ');
	if (!args)
		return (1);
	heredoc = d_create_heredoc(i);
	if (!heredoc)
	{
		d_free_tab(args);
		return (1);
	}
	if (d_put_args(args, cmd, heredoc, mshell) == 1)
		return (d_pipe_error2(args, heredoc));
	d_add_cmds(mshell, cmd);
	if (!cmd->infile)
		unlink(heredoc);
	else
		if (d_strncmp(cmd->infile, heredoc, d_strlen(cmd->infile) != 0))
			unlink(heredoc);
	free(heredoc);
	d_free_tab(args);
	return (0);
}

static void	d_parsing_pipe_if(t_cmds *tmp2)
{
	free(tmp2->cmd);
	tmp2->cmd = d_calloc(3, sizeof(char *));
	tmp2->cmd[0] = d_strdup("echo");
	tmp2->cmd[1] = d_strdup("-n");
	free(g_error[0]);
	g_error[0] = d_strdup("1");
}

static int	d_parsing_pipe(t_minishell *mshell, int i, char **tmp)
{
	t_cmds	*tmp2;

	d_free_tab(tmp);
	while (mshell->open_pipe == 1)
	{
		if (d_open_pipe(mshell, i) == 1)
			return (1);
		i++;
	}
	d_free_tab(g_error);
	g_error = d_calloc(3, sizeof(char *));
	if (!g_error)
		return (1);
	g_error[0] = d_strdup("0");
	tmp2 = mshell->cmds;
	while (tmp2)
	{
		if (!tmp2->cmd[0])
			d_parsing_pipe_if(tmp2);
		tmp2 = tmp2->next;
	}
	return (0);
}

int	ft_parsing(char *input, t_minishell *mshell)
{
	int		i;
	char	**tmp;
	t_cmds	*cmd;

	i = -1;
	mshell->nb_sq = 0;
	mshell->nb_dq = 0;
	if (d_check_end(input) == 1)
		return (1);
	if (d_check_quotes(input, mshell) == 1)
		return (1);
	tmp = d_split(input, '|');
	if (!tmp)
		return (1);
	while (tmp[++i])
	{
		cmd = d_init_cmds();
		tmp[i] = d_check_vars(tmp[i], mshell);
		if (!cmd || !tmp[i])
			return (1);
		if (d_parsing_args(mshell, cmd, tmp[i], i) == 1)
			return (d_pipe_error(tmp, cmd));
		d_check_pipe(input, mshell);
	}
	return (d_parsing_pipe(mshell, i, tmp));
}
