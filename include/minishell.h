/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:02:11 by smolines          #+#    #+#             */
/*   Updated: 2024/12/20 14:11:53 by aubertra         ###   ########.fr       */
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
	DIR,
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
	int		space; //1 if precedant char is space, 0 otherwise
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
	int		heredoc_count;
	int		heredoc_quotes;
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
	int			type;
	int			sec_type;
	char		*word;
	t_token		*token_first;
	int			size_token; //voir si necessaire
	t_cmd		*cmd_first;
	int			size_cmd;
	t_export	*export_first;
	int 		exit_status;
	t_env		*env_first;
} t_manager;


//cmd_path
char		*get_path(t_env *s_env);
char		*find_path(char *cmd, t_env *s_env, t_manager *manager);
char		*join_path(char *path, char *cmd, t_manager *manager, char **paths);
char		*absolute_path(char *cmd, t_manager *manager);

//cmd_test_path
char		*create_and_check_path(char *path, char *cmd, t_manager *manager, char **paths);
void		update_right_path(char **right_path, char *new_path);
char		*test_path(char **paths, char *cmd, t_manager *manager);

//debug
void		print_env(char **env_arr);
void		token_display(t_token *token);
void		cmd_display(t_cmd *cmd);

//env
char		*get_name(char *str);
char		**convert_env(t_env *s_env);
char		*get_content(char *str);
t_env		*handle_env(char **env);
int			envsize(t_env *lst);

//errno
int			errno_to_str(int errno_value, char* err_str);
char		*errno_inorder(char* err_str, int i);
int			expand_errno(t_manager *manager);

//error
int			parsing_error(t_manager *manager, int code);
int			parsing_error_op(t_manager *manager, int code, char operator, char dble_op);
int			access_error(t_manager *manager, int code, char *str);
int			cmd_error(t_manager *manager, int code, char *cmd);
int			open_close_error(t_manager *manager, int code);
//int dir_error(t_manager *manager, int code, char *word);

//exec_child
int			handle_input_redirection(t_cmd *cmd, int *previous_fd);
int			handle_output_redirection(t_cmd *cmd);
int			child_process(t_cmd *cmd, int *previous_fd, t_env *s_env, t_manager *manager);

//exec
int 		handle_heredoc(t_manager *manager, t_cmd *current_cmd, 
							int *previous_fd, t_env *s_env);
int			setup_pipe_and_fork(t_cmd *current_cmd, t_manager *manager);
int			close_fds(t_cmd *current_cmd, int *previous_fd, t_manager *manager);
int			execution(t_manager *manager, t_env *s_env);
int			waiting(int id_last);

//expand_cut
int			get_cut_length(char *str, int pos);
void		copy_without_expand(char *str, char *result, int pos);
char		*cut_expand(char *str, int pos);

//expand_replace
int			replexpand_length(char *str, int pos, char *expansion);
void		replexpand_copy(char *str, char *result, int pos, char *expansion);
char		*replace_expand(char *str, int pos, char *expansion);

//expand
int		expand(t_token *token, t_env *s_env);
char	*get_toexpand(char *str, int i);
char	*expand_exists(char *to_expand, t_env *s_env);
void	expand_dquote(t_token *current_token, t_env *s_env);
char	*expand_heredoc(char *current_line, t_env *s_env);

//fill_cmd_args
int			count_args(t_token *current);
char		**allocate_args(int cmd_count);
t_token		*fill_args_values(t_token *current, char **args, int cmd_count);
t_token		*fill_args(t_token *current, t_cmd *cmd, t_manager *manager);

//fill_cmd_expand
int			exploop_env_var(t_token *current_token, t_env *s_env, t_manager *manager);
int			exploop_dquote(t_token *current_token, t_env *s_env, t_manager *manager);
int			expand_loop(t_token *current_token, t_env *s_env, t_manager *manager);

//fill_cmd
int			redir_loop(t_token *current_token, t_cmd *cmd, t_manager *manager);
t_token		*cmd_loop(t_token *current_token, t_cmd *cmd, t_manager *manager);
int			fill_cmd(t_manager *manager, t_env *s_env);

//free_manager
void		free_token(t_token *token);
void		free_export(t_export *export);
void		free_cmd(t_cmd *cmd);
void		free_manager(t_manager *manager);
void		free_env(t_env *env);

//free
int			closing(t_cmd *cmd, int *previous_fd, t_manager *manager);
void		free_path(char **paths);
int			unlink_heredoc(t_manager *manager);
void		free_cmd_args(char **args);

//handle_files
int			check_heredoc(t_manager *manager);
int			check_infile(char *infile, t_manager *manager);
int			check_outfile(char *outfile, t_manager *manager);
int			create_doc(t_manager *manager, int *previous_fd, 
						t_cmd *current_cmd, t_env *s_env);
int			create_doc_loop(int *previous_fd, t_manager *manager, 
						t_cmd *current_cmd, t_env *s_env);

//oplist_manager
t_manager	*init_manager(t_manager *manager, t_env first_env, int exitcode);

//Operations sur liste token
void		*token_add_new(t_token *new_token, t_token **token);
t_token		*token_new(int prec_space, t_manager *manager);
void		token_add_back(t_token **token, t_token *new_token);
t_token		*token_last(t_token *token);

//oplist_env
t_env		*env_new(char *str);
void		env_add_back(t_env *first_env, char *str);
t_env		*env_last(t_env *env);
void		env_display(t_env *env);

//oplist_cmd
void		create_cmd_list(t_cmd *new_cmd, int cmd_node_count, t_manager *manager);
t_cmd		*cmd_new(void);
void		cmd_add_back(t_cmd *cmd, t_cmd *new_cmd);
t_cmd		*cmd_last(t_cmd *cmd);

//parsing_dir
int			is_a_dir(char *line, int i);
int			handle_dir(t_manager *manager, char *line, int i, t_token *current);

//parsing_heredoc
int			quotes_before(char *str, int i);
int			get_size_lim(char *limiter);
char		*fill_lim(char *limiter, t_manager *manager, int i);
int			parse_lim(t_token *current_token, t_cmd *cmd, t_manager *manager);
int			heredoc_quotes(char *line, int i, t_manager *manager);


//parsing space_operator
int			only_space(char *str);
int			is_symbols(char c);
int			only_space_symbols(char *str);
int			is_operators(t_manager *manager, char *line, int i);
int			check_operator_err(t_manager *manager, char *line, int i);
int			verif_operator(t_manager *manager, char *line, int i, int *type);

//parsing_utils
int			handle_quote(char *line, int i, t_manager *manager);
int			regular_word(t_manager *manager, char *line, int i);
int			count_quotes(t_manager *manager, char *line, char quote1, char quote2);

//parsing_utils2
int			handle_secondary_type(t_manager *manager, char *line, int i);
int			handle_redir(t_manager *manager, char *line, int i);
int			handle_pipe(t_manager *manager, char *line, int i);
int			is_an_expand(char *line, int i);
int			handle_env_pars(t_manager *manager, char *line, int i);

//parsing
int			handle_parsing_errors(t_manager *manager, char *line);
int			skip_spaces(char *line, int i, int *prec_space);
int			process_token(t_manager *manager, char *line, int i); 
int			parsing(t_manager *manager, char *line);
int			token_error(t_manager *manager);

#endif