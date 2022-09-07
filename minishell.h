/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:16:07 by ael-idri          #+#    #+#             */
/*   Updated: 2022/09/05 19:14:23 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define WORD 0
# define SPACE 1
# define D_QUOTE 2
# define S_QUOTE 3
# define PIPE 4
# define DOLLAR 5
# define REDIREC_IN 6
# define REDIREC_OUT 7
# define APPEND 8
# define HEREDOC 9
# define EOL 10

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <strings.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_global
{
	int			in_child;
	int			herdoc;
	int			errno;
	int			exit_signal;
}				t_global;

typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_ioredirect
{
	int					type;
	int					fd;
	char				*file_name;
	struct s_ioredirect	*next;
}						t_ioredirect;

typedef struct s_cmd_suffix
{
	char				**args;
	t_ioredirect		*redirection;
}						t_cmd_suffix;

typedef struct s_command
{
	t_ioredirect		*cmd_pref;
	t_cmd_suffix		*cmd_suff;
	char				*cmd;
}						t_command;

typedef struct s_info
{
	int					status;
	int					pfd[2];
	int					in;
	int					erreur_fork;
}						t_info;

typedef struct s_pipe_seq
{
	pid_t				pid;
	t_command			*cmd;
	t_token				*token;
	t_info				*info;
	int					input;
	int					output;
	int					test;
	struct s_pipe_seq	*next;
}						t_pipe_seq;

typedef struct s_env
{
	char				*value;
	char				*key;
	struct s_env		*next;
}						t_env;

// main_exec.c
typedef struct s_info_join
{
	char				**join_arg;
	char				**args;
	int					i;
	int					j;
	int					len;
	char				*cmd;
}						t_info_join;

//		global
t_global	g_global;

//		./lexer/token.c
int			tokenizer(char *line, t_token **token);

//		./lexer/syntax_error.c
int			prev_is_redirection(t_token *tok);
int			syntax_error(t_token **token, t_env *env);

//		./lexer/change_dollars.c
int			change_dollars(t_token **token, t_env *env);

//		./lexer/creat_dollar_tokens.c
t_token		*space_token(void);
t_token		*empty_token(void);
void		add_token_to_main_token(t_token **head, t_token **token,
				t_token **new, t_token **tem);
void		add_back_token(t_token **head, t_token **new);
int			creat_dollar_token(t_token **head, char *data,
				t_token *tok, t_env *env);

//		./lexer/split_by_spaces.c
char		**split_whitespaces(char *s);
int			is_space(char s);

//		./lexer/join_quote.c
int			join_quotes(t_token **token, t_env *env);

//		./lexer/join_words.c
int			join_words(t_token **token);

//		./lexer/heredoc_delimiter.c
int			prev_is_hdoc(t_token *token);
int			join_heredoc_delimiter(t_token **token);

//		./lexer/tokens_utils.c
t_token		*last_token(t_token *token);
void		free_tokens(t_token **token);
char		*get_env_value(char *str, t_env *env);
char		*join_quotes_data(char **s1, char *s2);
int			prev_is_hdoc(t_token *token);

// 		./lexer/token_tools.c
void		delete_empty_quotes(t_token **head, t_token **run);
char		*add_word(char *line, int *i);
char		*dollar_v(char *str, t_token *tok, t_env *env);
char		*add_size2_token(char *line, int *i);
int			what_token(char *line, int i);

//		./lexer/manage_error.c
int			manage_syntax_error(int type, t_token **token);
int			malloc_error(t_token **token);
// 		./lexer/ft_creat_quots.c
t_token		*creat_s_quote_token(t_token *token);

//		./parser/parser.c
int			parser(t_token **token, t_pipe_seq **pipe_seq);

//		./parser/free_pipe_seq.c
void		free_pipe_seq(t_pipe_seq **pipe_seq);

//		./parse/get_pipe_seq.c
int			get_pipe_seq(t_pipe_seq **pipe_seq, t_token **token);

//		./parser/get_command.c
int			get_command(t_token **token, t_command **cmd);

//		./parser/get_cmd_suff.c
int			get_cmd_suff(t_token **token, t_cmd_suffix **cmd_suff);

//		./parser/get_redirection.c
bool		is_redirection(t_token **search);
int			get_redirection(t_token *token, t_ioredirect **cmd_pref);

//		./parser/read_pipe_seq.c
void		read_pipe_seq(t_pipe_seq *pipe_seq);

//		./signals/signal_handler.c
void		minishell_signal(void);
void		herdoc_signal_handler(void);
void		quit_handler(int signum);
void		herdoc(int signum);
// ./main.c
void		ft_inc_shlvl(t_env *val);
void		is_builtins(t_pipe_seq *comd, t_env **p);
int			ft_is_builtins(t_pipe_seq *comd);
int			main(int ac, char **av, char **env);

//execution/builtin/utils_export.c
void		ft_tri(char **tableau);
char		*ft_key_export(char *envp);
char		**ret_tab(t_env *val);
int			check_erreur_in_export(char *args);
int			ft_strlen_key(char *envp);

//execution/builtin/builtin_export.c
void		add_env(t_env **val, char *args);
void		change_value(t_env	*node, char	*value);
void		add_arg_in_export(t_pipe_seq *cmd, t_env **val);
int			ft_export(t_env **val);
int			*builtin_export(t_env **val, t_pipe_seq *cmd);

//execution/builtin/add_export.c
t_env		*get_env_node(char *str, t_env *head);
void		ft_add(t_env **val, char *key, char *value);
void		add_pwd_old(t_env *val);

//execution/builtin/builtin_cd.c
void		builtin_cd(t_pipe_seq *arg, t_env *head);
void		cd_args_not_exist(t_env *head,	t_env *pwd, t_env *oldpwd);
void		ft_is_pwd_deleted(t_pipe_seq *arg, t_env *val);
void		ft_cd(t_pipe_seq *arg,	t_env	*pwd, t_env	*oldpwd);
void		ft_is_moins(t_pipe_seq *arg, t_env *pwd, t_env *oldpwd, char *args);

//execution/builtin/builtin_echo.c
void		is_args(char **args, int *i);
int			builtin_echo(t_pipe_seq *val);
int			check_arg(char *args);

//execution/builtin/builtin_env.c
t_env		*list_env(char **env_array);
t_env		*ft_list(t_env *head, char **env_array);
char		*ft_key(char *envp);
int			ft_strchr1(const char *s, int c);
int			*builtin_env(t_env *val);

//execution/builtin/builtin_exit.c
void		bultins_exit(t_pipe_seq *p);

//execution/builtin/builtin_pwd.c
void		builtin_pwd(t_env *val);

//execution/builtin/builtin_unset.c
void		ft_unset(t_env **val, char *args);
void		free_first(t_env **env);
void		unset_next(t_pipe_seq *arg, t_env *val);
int			check_erreur_in_unset(char *args);
int			builtin_unset(t_pipe_seq *arg, t_env **val);

// ./execution/non_bultins/main_exec.c
void		ft_execution(t_env **p, t_pipe_seq *pipe_seq);
char		**join_arg_cmd(t_pipe_seq *p);
int			ft_exec(t_env **env, t_pipe_seq *cmd);
int			ft_main_execv(t_env **env, t_pipe_seq *cmd);
int			ft_access(t_env *env, t_pipe_seq *cmd, char **args, char **envp);

// ./execution/non_bultins/utils_non_builtin.c
void		ft_perror(t_pipe_seq *cmd);
char		**env_to_str(t_env *env);
int			ft_size(t_env *lst);
int			ft_strlen_deux(char **str);

// ./execution/redirection/herdoc.c
int			write_in_herdoc(char *dilemiter, t_env *env);
int			ft_herdoc(char *dilemiter, t_pipe_seq *p, t_env *env);
int			free_herdoc(int fd, char *name_file, char *buf);

// ./execution/redirection/redir_herdoc.c
void		input_herdoc(t_pipe_seq *p, t_ioredirect *cmd, t_env *env);
void		ft_multiple_redirection(t_pipe_seq *p, t_env *env);
void		ft_multiple_redirection_pref(t_pipe_seq *p, t_env *env);
void		ft_is_redirection(t_pipe_seq **p, t_env *env);

// ./execution/pipe/ft_pipe.c
void		dup_file(t_pipe_seq *pi, t_info *info);
void		fork_pipe(t_pipe_seq *pi, t_env *env, t_info *info);
void		ft_execute_pipe(t_pipe_seq *pi, t_env *env);
int			wait_pid(int status);
int			ft_pipe(t_env *env, t_pipe_seq **p, t_info	*info);

// ./execution/free.c
void		free_t_env(t_env *env);
void		free_line(char **line);
void		free_tab(char ***tab);
#endif
