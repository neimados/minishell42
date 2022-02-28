/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:24:12 by dso               #+#    #+#             */
/*   Updated: 2022/02/28 20:04:31 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 1

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <termios.h>

typedef struct s_cmds		t_cmds;
typedef struct s_minishell	t_minishell;
typedef struct s_var		t_var;
typedef struct s_parsing	t_parsing;

char						**g_error;

struct s_cmds
{
	char		**cmd;
	char		*infile;
	int			type;
	int			heredoc;
	char		*outfile;
	t_cmds		*next;
	int			pipe[2];
	pid_t		pid_child;
};

struct s_parsing
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		fd;
	int		sign;
	int		in;
	int		out;
	int		end;
	int		start;
	int		sq;
	int		dq;
	char	*tmp;
};

struct s_minishell
{
	t_cmds		*cmds;
	int			nb_sq;
	int			nb_dq;
	int			nb_pipe;
	char		**g_mini_env;
	char		*pwd;
	int			open_pipe;
};

// parsing
void	ft_input(char **envp, t_minishell *mshell);
void	ft_cp_env(char **envp, t_minishell *mshell);
void	d_search_pwd(t_minishell *mshell);
int		ft_chr_old(char **envp);
int		d_search_shlvl(char **envp);
void	d_cp_env_err(t_minishell *mshell);
int		ft_parsing(char *input, t_minishell *mshell);
void	d_check_pipe(char *input, t_minishell *mshell);
int		d_open_pipe(t_minishell *mshell, int heredoc_num);
int		d_pipe_error(char **tmp, t_cmds *cmd);
int		d_pipe_error2(char **args, char *heredoc);
int		d_pipe_return(char **tmp, char *input);
char	**d_split(char *s, char c);
void	freemalloc(char **strs);
int		d_loop_countwords(char const *str, char c, int i);
int		d_loop_malloctab(int i, char const *str);
int		d_loop_filltab(t_parsing *p, char const *str, char **strs);
int		d_skip_filltab(t_parsing *p, char const *str);
char	*d_strdup(const char *str);
size_t	d_strlen(const char *str);
void	*d_calloc(size_t count, size_t size);
char	*d_strjoin(char *s1, char *s2);
char	*d_itoa(int n);
int		d_atoi(const char *str);
int		d_strncmp(const char *a, const char *b, size_t size);
char	*d_substr(char const *s, unsigned int start, size_t len);
void	d_free_tab(char **tab);
void	d_init_struct(t_minishell *mshell);
t_cmds	*d_init_cmds(void);
void	*d_add_cmds(t_minishell *mshell, t_cmds *cmd);
int		d_count_tab(char **tmp);
int		d_check_quotes(char *input, t_minishell *mshell);
int		d_check_end(char *input);
int		d_count_cmds(char **args);
int		d_put_cmds(char **args, t_cmds *cmd);
char	*d_trim_cmd(char *to_trim);
char	*d_create_heredoc(int i);
int		d_start_heredoc(char *hd_stop, char *heredoc, t_minishell *mshell);
int		d_check_hd_quotes(char *hd_stop, char c);
char	*d_trim_hdstop(char *hd_stop);
int		d_fork_error_heredoc(char *stop);
char	*d_check_vars(char *tmp, t_minishell *mshell);
char	*d_check_path(char *variable, char *env);
char	*d_var_err(void);
int		d_loop_vars_if(char *tmp, int i);
char	*d_loop_vars3(char *tmp, int i, t_minishell *mshell, char *str);
int		d_skip_vars3(char *tmp, int i);
int		d_put_args(char **args, t_cmds *cmd,
			char *heredoc, t_minishell *mshell);
int		d_args_in(char *arg, t_cmds *cmd,
			t_minishell *mshell, t_parsing *p);
int		d_args_heredoc(char *arg, t_minishell *mshell,
			t_cmds *cmd, t_parsing *p);
int		d_args_out(char *arg, t_cmds *cmd, t_minishell *mshell, t_parsing *p);
void	d_putstr_fd(char *s, int fd);
void	d_putchar_fd(char c, int fd);
void	d_check_countwords(char c, int *i);
char	*d_strchr(const char *str, int c);
char	*get_next_line(int fd);
char	*d_strchr2(const char *str, int c);
char	*d_strjoin2(char *s1, char *s2);
char	*d_check_vars2(char *tmp, t_minishell *mshell);
int		d_skip_vars_hd(char *tmp, int i);
int		d_skip_vars3_hd(char *tmp, int i);
int		d_skip_vars2_hd(char *tmp, int i);
void	d_check_underscore(t_cmds *cmd, t_minishell *m);
void	d_replace_underscore(t_minishell *m);
char	*ft_strtrim(char const *s1, char const *set);

// exec
void	k_loop_forks(t_minishell *minishell);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strrchr(const char *str, int chr);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_error(char *str1, char *str2);
void	k_exec_builtins(char **cmd, t_minishell *minishell);
void	k_is_builtin_fct(char **cmd, t_minishell *minishell);
void	k_error(char *str1, char *str2);
void	k_exec_cmd(char **cmd, t_minishell *minishell);
int		k_loop_forks_check(int nbcmd,
			t_minishell *minishell, t_cmds *tmp, int i);
void	k_set_signals(int nbcmd, t_cmds *tmp, int i);
int		k_create_forks(int nbcmd, t_cmds *tmp,
			t_minishell *minishell, pid_t *forks);
void	k_forks_end(int i, t_minishell *minishell,
			t_cmds *tmp2, pid_t *forks);
void	k_child(t_minishell *minishell, int i);
void	k_unlink_heredoc(t_minishell *minishell, pid_t *forks);
int		k_count_cmds(t_cmds *tmp);
void	k_join_cmd(char **path, char **cmd);
int		k_search_path(t_minishell *minishell);
void	k_child_fd(t_cmds *tmp, t_minishell *minishell);
t_cmds	*k_child_close_pipe(int i, t_cmds *tmp);
void	k_child_dup(t_cmds *tmp, int in, int out);

// builtin
void	ft_pwd(char **cmds, t_minishell *mshell);
void	ft_exit(t_minishell *mshell, char **cmds, int key);
void	ft_env(char **cmds, t_minishell *mshell);
void	ft_echo(char **cmds);
void	ft_export(char **cmds, t_minishell *mshell);
void	ft_cd(char **cmds, t_minishell *mshell);
void	ft_unset(char **cmds, t_minishell *mshell);
void	d_print_declare_export(t_minishell *mshell);
int		d_check_export(char *cmd);
int		k_cd_ignore(char **tmp2, char **cmds);
int		k_cd_slash(t_minishell *minishell, int j, char **cmds);
int		k_cd_others(t_minishell *minishell, int j, char **cmds, char *tmp);
int		k_cd_type2(t_minishell *minishell, int j, char **cmds);
int		k_cd_type(t_minishell *minishell, char **cmds, int j);
int		k_cd_user2(int i, t_minishell *m, int j);
int		k_cd_user(t_minishell *m, int j);
int		k_cd_dotdot(t_minishell *minishell, int j);
int		k_cd_dash2(int j);
int		k_cd_dash(t_minishell *m, int j);
void	k_free_oldpwd(char **oldsplit, char *oldjoin);
void	k_error(char *str1, char *str2);
int		ft_strncmp(const char *first, const char *second, size_t len);
char	**k_cp_env(t_minishell *minishell);
int		k_search_pwd(t_minishell *m);
int		k_dotdot2(t_minishell *minishell, int j);
void	k_free_end(char *old, char **tmp2, char *pwd);
int		k_cd_oldpwd(t_minishell *minishell, char *old);
int		k_cd_dash_loop(int j, t_minishell *m, int i);
void	k_set_gerror(void);
void	k_child_error_exit(t_cmds *tmp);
char	*d_export_quotes(char *str);

//signals
void	ft_terminal(int echo);
void	sigint_handler(int keycode);
void	sigint_handler_child(int keycode);
void	sigint_handler_spec(int keycode);
void	sigint_handler_minishell(int keycode);
void	sigint_handler_hd(int keycode);

#endif

// CD TO FIX (Lien symbolique, .., leaks, unset PWD)