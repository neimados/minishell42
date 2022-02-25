/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:29:51 by dso               #+#    #+#             */
/*   Updated: 2022/02/21 12:22:04 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_exist_var_err(int i, char *tmp, char *tmp2)
{
	free(tmp2);
	free(tmp);
	return (i);
}

static int	d_exist_var(char **env, char *cmd, int i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	tmp = d_substr(cmd, 0, i);
	if (!tmp)
		return (-1);
	i = -1;
	while (env[++i])
	{
		while (env[i][j] && env[i][j] != '=')
			j++;
		tmp2 = d_substr(env[i], 0, j);
		if (!tmp || !tmp2)
			return (-1);
		if (d_strncmp(tmp, tmp2, d_strlen(tmp)) == 0)
			return (d_exist_var_err(i, tmp, tmp2));
		j = 0;
		free(tmp2);
	}
	free(tmp);
	return (0);
}

static void	d_loop_put_export(t_minishell *m, char *cmd, int exist, char **new)
{
	int		i;

	i = 0;
	while (m->g_mini_env[i])
	{
		if (exist != 0 && exist == i)
			new[i] = d_strdup(cmd);
		else
			new[i] = d_strdup(m->g_mini_env[i]);
		i++;
	}
	if (exist == 0)
		new[i] = d_strdup(cmd);
}

static char	**d_put_export(char *cmd, t_minishell *mshell)
{
	char	**new;
	int		size;
	int		i;
	int		exist;

	i = 0;
	new = NULL;
	size = d_count_tab(mshell->g_mini_env);
	exist = d_exist_var(mshell->g_mini_env, cmd, i);
	if (exist == -1)
		return (NULL);
	if (exist == 0)
		new = d_calloc((size + 2), sizeof(char *));
	else
		new = d_calloc((size + 1), sizeof(char *));
	if (!new)
		return (NULL);
	d_loop_put_export(mshell, cmd, exist, new);
	return (new);
}

void	ft_export(char **cmds, t_minishell *mshell)
{
	int		i;
	char	**new_env;

	i = 1;
	if (!cmds[1])
		return (d_print_declare_export(mshell));
	while (cmds[i])
	{
		if (cmds[i][0] == '=')
		{
			printf("export : \'%s\': not a valid identifier\n", cmds[i]);
			return ;
		}
		else
		{
			new_env = d_put_export(cmds[i], mshell);
			if (!new_env)
				exit(EXIT_FAILURE);
			d_free_tab(mshell->g_mini_env);
			mshell->g_mini_env = new_env;
		}
		i++;
	}
	return ;
}
