/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:02:11 by smolines          #+#    #+#             */
/*   Updated: 2024/12/11 16:37:03 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <ctype.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <errno.h> 
# include <readline/readline.h>
# include <readline/history.h>

// Token type enumeration
typedef enum e_token_type
{
    CMD_ARG,      // For commands and arguments
	SIMPLE_QUOTE, //For ''
	DOUBLE_QUOTE, // For ""
    PIPE,      // For '|'
    REDIR_IN,  // For '<'
    REDIR_OUT, // For '>'
    REDIR_APPEND, // For '>>'
    REDIR_HEREDOC, // For '<<'
    ENV_VAR, // For environment variables start with $
	EXIT_STAT, // for $?
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}   t_token_type;

typedef struct s_token t_token;
typedef struct s_cmd t_cmd;
typedef struct s_env t_env;
typedef struct s_export t_export;

struct s_token
{
	char	*value;
	int		type;
//	int		flag; //use as a bool i.e. 0 or 1
	t_token	*next;
	t_token	*prev;
};

struct s_cmd
{
	int		index;
	char	*path;
	char	**args;
	char	*infile;
	char	*lim;
	int		heredoc_priority;
	char	*outfile;
	int		append;
	int		pfd[2];
	t_cmd	*next;
	t_cmd	*prev;
};


struct s_env
{
	char	*field;
	char	*content;
	t_env	*next;
	t_env	*prev;
};

struct s_export
{
	char		*field;
	char		*content;
	t_export	*next;
	t_export	*prev;
};

typedef struct s_manager
{
	t_token		*token_first;
	t_token		*token_last;
	int			size_token;
	t_cmd		*cmd_first;
	t_cmd		*cmd_last;
	int			size_cmd; //size cmd a update dans le truc de cmd
	t_export	*export_first;
	t_export	*export_last;
	int			size_export;
	int 		exit_status;
} t_manager;


//parsing
int		parsing(t_manager *manager,char *line);
int		verif_operator(t_manager *manager, char *line, int i, int *type);

//parsing_utils 1 & 2
int		check_operator_err(t_manager *manager, char *line, int i);
int		is_operators(t_manager *manager, char *line, int i);
int		handle_quote(char *line, int i, int type, char **word);
int		regular_word(t_manager *manager, char *line, int i, char **word);
int		count_quotes(t_manager *manager, char *line, char quote1, char quote2);
int		handle_redir(t_manager *manager, char *line, int i, char **word);
int		token_error(t_manager *manager);
int		handle_pipe(t_manager *manager, char *line, int i, char **word);

//oplist_manager
t_manager	*init_manager(t_manager *manager);

//Operations sur liste token
void	*token_add_new(t_token *new_token, t_token **token);
t_token	*token_new(char *word, int flag);
void	token_add_back(t_token **token, t_token *new_token);
t_token	*token_last(t_token *token);
void	token_display(t_token *token);

//free
void	free_token(t_token *token);
int		closing(t_cmd *cmd, int *previous_fd, t_manager *manager);
void	free_path(char **paths);
void	unlink_heredoc(t_manager *manager);
void	free_env(t_env *env);
void	free_export(t_export *export);
void	free_cmd_args(char **args);
void	free_cmd(t_cmd *cmd);
void	free_manager(t_manager *manager);

//error
int parsing_error(t_manager *manager, int code);
int	parsing_error_op(t_manager *manager, int code, char operator, char dble_op);
int access_error(t_manager *manager, int code, char *str);
int cmd_error(t_manager *manager, int code, char *cmd);
int open_close_error(t_manager *manager, int code);

//display
void	token_display(t_token *token);

//env
char		*get_name(char *str);
char	**convert_env(t_env *s_env);
char		*get_content(char *str);
t_env		*handle_env(char **env);

//oplist_env
t_env		*env_new(char *str);
void		env_add_back(t_env *first_env, char *str);
t_env		*env_last(t_env *env);
void		env_display(t_env *env);

//cmd_path
char	*get_path(t_env *s_env);
char	*find_path(char *cmd, t_env *s_env, t_manager *manager);
char	*join_path(char *path, char *cmd, t_manager *manager, char **paths);
char	*test_path(char **paths, char *cmd, t_manager *manager);
char	*absolute_path(char *cmd, t_manager *manager);

//oplist_cmd
void	create_cmd_list(t_cmd *new_cmd, int cmd_node_count, t_manager *manager);
t_cmd	*cmd_new(void);
void	cmd_add_back(t_cmd *cmd, t_cmd *new_cmd);
t_cmd	*cmd_last(t_cmd *cmd);
void	cmd_display(t_cmd *cmd);

//expand
void	expand(t_token *token, t_env *s_env);
char	*get_toexpand(char *str, int i);
char	*expand_exists(char *to_expand, t_env *s_env);
char	*replace_expand(char *str, int pos, char *expansion);
void	expand_dquote(t_token *current_token, t_env *s_env);
char	*cut_expand(char *str, int pos);

//fill cmd struct
int		fill_cmd(t_manager *manager, t_env *s_env);
t_token	*fill_args(t_token *current, t_cmd *cmd, t_manager *manager);
void	expand_loop(t_token *current_token, t_env *s_env);
t_token	*cmd_loop(t_token *current_token, t_cmd *cmd, t_manager *manager);
int		redir_loop(t_token *current_token, t_cmd *cmd, t_manager *manager);

//exec
int		execution(t_manager *manager, t_env *s_env);
int		child_process(t_cmd *cmd, int *previous_fd, t_env *s_env, t_manager *manager);
int		waiting(int id_last);

//handle files
int		check_infile(char *infile, t_manager *manager);
int		check_outfile(char *outfile, t_manager *manager);
int		check_heredoc(t_manager *manager);
int	create_doc(t_manager *manager, int *previous_fd, char *lim);

#endif
