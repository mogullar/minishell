/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:35:38 by mogullar          #+#    #+#             */
/*   Updated: 2023/11/05 20:35:38 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define RD_L 1
# define RD_R 2
# define RD_RR 3
# define RD_LL 4
# define PIPE 5
# define COMMAND 6
# define STRING 7

typedef struct s_data
{
	struct s_token	*tokens;
	struct s_pata	*mini;
	char			**vars;
	char			*command_line;
	char			path[4096];
	char			**contents;
	int				*types;
	char			**envp;
	char			**quote;
	char			**dquote;
	int				**fds;
	int				red_ll_fd;
	int				red_l_fd;
	int				red_r_fd;
	int				icopy;
	int				counter_quote;
	int				counter_dquote;
	int				exit_status;
}	t_data;

typedef struct s_parser
{
	char			**commands;
	char			**red;
	int				in_fd;
	int				out_fd;
	int				hd_fd;
	struct s_parser	*next;
}	t_parser;

typedef struct s_pipe
{
	int	fd[2];
	int	pid;
}	t_pipe;

typedef struct s_pata
{
	t_parser	*arr;
	t_pipe		*pipe;
	int			p_count;
}	t_pata;

typedef struct s_token
{
	struct s_contents	*contents;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_contents
{
	char				*content;
	int					type;
	int					quote_type;
	struct s_contents	*next;
	struct s_contents	*prev;
}	t_contents;

typedef struct s_append_var
{
	char				*content;
	struct s_append_var	*next;
	struct s_append_var	*prev;
}	t_append_var;

typedef struct s_globals
{
	int	a;
	int	test1;
	int	test2;
	int	child_pid;
}	t_globals;

t_globals	g_global;

void		execute(t_data *data);
char		*fill_content(t_data *data, int j, int len, char **content);
void		go_to_home(char **path, t_data *data);
int			cd(t_data *data, t_parser *a);
int			pwd(t_data *data);
void		printdquote(char *content, int *location);
int			quotecount(t_data *data);
int			dquotecount(t_data *data);
char		*for_var(char **envp, int i);
char		*isenv_checker(t_data *data, char *var);
char		*free_isenv(t_data *data, char ***split, char *if_val, int i);
char		*isenv(t_data *data, char *var);
char		*fordollar2(t_data *data, int *j);
void		if_not_n(int n);
int			if_option(char *option, int *n, int location);
int			echo(t_data *data, t_parser *a);
int			if_not_var(t_data *data, char **content);
int			find_index(char *content, int *index);
int			main_loop_ex(t_data *data, t_append_var ***len_strs, int **len,
				char *content);
void		if_only_export(t_data *data, t_parser *a);
int			export(t_data *data, t_parser *a);
void		only_export(t_data *data);
void		if_var_exist_control(t_data *data, char **content, int i, int k);
int			if_var_exist(t_data *data, char **content,
				char ***content_val, int index);
void		fill_env(t_data *data, int len, t_append_var *tmp,
				t_append_var *len_strs);
void		fill_for_strs(t_data *data, int ***len, t_append_var ****len_strs,
				char *content);
void		fill_for_strs_unset(t_data *data, int **len,
				t_append_var ***len_strs, char *content);
char		*for_content(t_data *data_tmp, char **content, int *i, int *index);
void		change_var(t_data *data, int index, char **content_val);
int			free_of_unset(t_data *data, char **split, char *content);
int			free_of_unset2(t_data *data, char **split, char *content);
int			main_loop_unset(t_data *data, t_append_var **len_strs,
				int *len, char *content);
char		**remove_from_env(t_data *data, int len, t_append_var *len_strs);
void		if_exist(t_data *data, int len, t_append_var *tmp,
				t_append_var *len_strs);
int			unset(t_data *data, t_parser *a);
void		free_len_strs(t_append_var *len_strs, t_append_var *tmp);
int			free_of_export(t_data *data, char *content,
				char ***content_val, int cntrol);
int			ft_free_content(char **split, char *content);
int			env(t_data *data);
void		ft_execve(t_data *data, t_parser *a, char *cmnd);
void		ft_bexit(t_data *data, int exitcode);
int			ft_exit(t_data *data);
int			if_our_command(t_data *data, t_parser *a);
int			is_our_command(char *content);
int			fill_tokens_quote(t_data *data, int j, int *len);
int			fill_tokens_dquote(t_data *data, int j, int *len);
int			fill_tokens_specials(t_data *data, int j, int *len);
int			fill_tokens_default(t_data *data, int j, int *len);
void		lexer2(t_data *data);
void		lexer_init(t_data *data);
int			fillforcontents(t_data *data, int *len, int i);
void		fill_for_tokens(t_data *data);
int			continue_fillquotes(t_data *data, int i);
void		fillforquotes(t_data *data, int *i);
int			continue_filldquotes(t_data *data, int i);
void		fillfordquotes(t_data *data, int *i);
void		lexer(t_data *data);
char		**allocate_memory(int k, t_data *data, int token, char ***commands);
int			to_commandline(t_data *data, int i);
void		token_typer(t_data *data);
void		get_token_type(t_data *data);
void		parser(t_data *data);
void		fill_arrays(t_data *data, char **contents,
				int *types, char *content);
void		go_to_back(t_data *data, int i);
int			*continue_contents(t_data *data, char ***contents, int **types);
char		**contents_splitter(t_data *data, int len);
char		**to_contents(t_data *data);
char		*fill_for_commands(t_data *data, int k, int *j);
void		fill_the_arrays(int *k, t_data *data,
				char ***commands, char ***red);
void		find_len(t_data *data, int *len, int *i);
char		*join_content(t_data *data);
void		loop(t_data data);
int			ft_her(char *delim, t_data data, int i);
void		ft_init_pipe(t_pata *mini);
void		close_fds(t_data *x);
void		ft_wait(t_data *data, t_pata *mini);
void		ft_wait_single(pid_t pid, t_data *data);
void		ft_heredoc_init(t_data data, t_pata *mini);
int			ft_check_in(char **redir, t_data *data);
void		take_outputs(t_data *data, t_parser *a);
int			ft_check_last(char **redir);
int			ft_check_out(char **redir);
void		if_multiple_commands(t_data *data, t_parser *a);
t_data		datacreate(t_data *data);
void		reset_values1(t_data *data);
void		reset_values(t_data *data);
void		fill_envp(t_data *data, char **envp);
void		close_heredoc(int sig);
void		sigquit_handler(int sig);
void		ft_handler(int sig);
void		delete_ctrl(void);
char		*ft_strjoin2(char *s1, char *s2);
int			ft_strcmp(const char *s1, const char *s2);
t_parser	*ft_lstlast_par(t_parser *lst);
t_parser	*ft_lstnew_parser(void);
void		ft_lstadd_back_par(t_parser **lst, t_parser *new);
int			pipe_counter(t_data *data);
int			counter_commands(t_data *data, int token, int k);
int			isspecialtype(int c);
int			isspecialchar(char c);
int			token_len(int i, t_data *data);
char		**from_env(t_data *data);
char		*find_path(t_data *data, char *cmnd);
int			ft_isalldigit(char *str);
void		free_arrays(char ***split, int i);
int			if_only_equal(char *content, int index);
int			ft_isalnum_str(char *content, int i);
void		reset_values1(t_data *data);
void		reset_values(t_data *data);
int			check_for_var(char *content, int j);
int			if_path_exist(t_data *data, t_parser *a);
int			if_command(t_data *data, int k);
void		ft_last(t_data *data, t_parser *a, int i);
char		**fill_vars(char *content);
int			check_for_errors(t_data *data);

#endif