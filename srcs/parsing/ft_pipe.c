/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:57:09 by dso               #+#    #+#             */
/*   Updated: 2022/02/25 15:29:16 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	d_pipe_child(void)
{
	int		fd;
	char	*input;

	fd = 0;
	signal(SIGINT, sigint_handler_hd);
	fd = open("/private/tmp/tmp_pipe", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		exit(EXIT_FAILURE);
	input = readline("> ");
	if (input == NULL)
	{
		close(fd);
		free(input);
		d_putstr_fd("syntax error: unexpected end of file\n", 2);
		exit(EXIT_FAILURE);
	}
	write(fd, input, d_strlen(input));
	close(fd);
	free(input);
	exit(EXIT_SUCCESS);
}

char	*d_pipe_fork(t_minishell *mshell)
{
	int		fd;
	pid_t	fork_pipe;
	char	*input;
	int		status[1];

	fd = 0;
	fork_pipe = fork();
	if (fork_pipe == -1)
		return (NULL);
	signal(SIGINT, sigint_handler_minishell);
	if (fork_pipe == 0)
		d_pipe_child();
	waitpid(fork_pipe, status, 0);
	if (WEXITSTATUS(status[0]) == 1)
	{
		mshell->open_pipe = 0;
		return (NULL);
	}
	fd = open("/private/tmp/tmp_pipe", O_RDONLY);
	if (fd == -1)
		return (NULL);
	input = get_next_line(fd);
	close(fd);
	unlink("/private/tmp/tmp_pipe");
	return (input);
}

char	*d_pipe_input(t_minishell *mshell)
{
	char	*input;

	input = d_pipe_fork(mshell);
	if (!input)
	{
		free(input);
		return (NULL);
	}
	if (d_check_end(input) == 1)
	{
		free(input);
		return (NULL);
	}
	if (d_check_quotes(input, mshell) == 1)
	{
		free(input);
		return (NULL);
	}
	return (input);
}

int	d_pipe_args(char *tmp, int heredoc_num, t_minishell *mshell, t_cmds *cmd)
{
	char	**args;
	char	*heredoc;

	args = d_split(tmp, ' ');
	if (!args)
		return (1);
	heredoc = d_create_heredoc(heredoc_num);
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

int	d_open_pipe(t_minishell *mshell, int heredoc_num)
{
	int		i;
	char	**tmp;
	t_cmds	*cmd;
	char	*input;

	i = 0;
	mshell->nb_sq = 0;
	mshell->nb_dq = 0;
	input = d_pipe_input(mshell);
	if (!input)
		return (1);
	tmp = d_split(input, '|');
	if (!tmp)
		return (1);
	while (tmp[i])
	{
		cmd = d_init_cmds();
		if (!cmd)
			return (1);
		if (d_pipe_args(tmp[i], heredoc_num, mshell, cmd) == 1)
			return (d_pipe_error(tmp, cmd));
		i++;
		d_check_pipe(input, mshell);
	}
	return (d_pipe_return(tmp, input));
}
