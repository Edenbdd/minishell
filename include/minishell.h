/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:02:11 by smolines          #+#    #+#             */
/*   Updated: 2025/01/02 15:22:54 by aubertra         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/time.h>
# include <errno.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

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
	EXIT_STAT, // for $? EST CE UTILISE ?
	DIREC, //if /
	ECHO, // !!! ATTENTION, ne rien ajouter entre ECHO et EXIT
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV, //built in env cmd
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
	int		cmd_done;
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
	int		is_builtin; //flag 1 if builtin, 0 otherwise
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
	int			heredoc_line;
	t_env		*env_first;
} t_manager;

//BUILT IN
//parsing_builtin
int    check_builtin(t_manager *manager, char *to_test);
int 	is_builtin(int type);
int		builtin_exec_path(t_manager *manager, t_cmd *cmd, int *previous_fd);

//env_builtin
int		handle_builtin_env(t_manager *manager, t_cmd *cmd);
int		new_exec(t_manager *manager, t_cmd *cmd, int i);
int 	access_error_env(t_manager *manager, int code, char *str);
void	env_display_builtin(t_env *env);

//env_builtin_args
char 	**fill_new_args(char **old_args, int i, int count);
int 	count_args_env(char **old_args, int i);
char    **copy_args(char **old_args, int i);

//oplist_export
void		export_display(t_export *export);
t_export	*export_last(t_export *export);
void		export_add_back(t_export *first_export, t_env *current_env);
t_export	*export_new(t_env *current_env);
t_export    *env_to_export(t_env *first_env);

//export_builtin
int			handle_builtin_export(t_manager *manager, t_cmd *cmd);

//unset


//CORE
//cmd_path
char		*get_path(t_env *s_env);
char		*find_path(char *cmd, t_env *s_env, t_manager *manager, int env_flag);
char		*join_path(char *path, char *cmd, t_manager *manager, char **paths);
char		*absolute_path(char *cmd, t_manager *manager, int env_flag);

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
int			expand_errno(t_manager *manager, int i);

//error
int			parsing_error(t_manager *manager, int code);
int			parsing_error_op(t_manager *manager, int code, char operator, char dble_op);
int			access_error(t_manager *manager, int code, char *str);
int			cmd_error(t_manager *manager, char *cmd, int exec_flag);
int 		system_function_error(t_manager *manager, int code);


//exec_child
int			handle_input_redirection(t_cmd *cmd, int *previous_fd, t_manager *manager);
int			handle_output_redirection(t_cmd *cmd, t_manager *manager);
int 		child_process(t_cmd *cmd, int *previous_fd, 
							t_manager *manager, char **to_execute);
int 		path_execution_heredocline(t_manager *manager, char **to_execute);

//exec
int 		handle_heredoc(t_manager *manager, t_cmd *current_cmd, 
							int *previous_fd, t_env *s_env);
int			setup_pipe_and_fork(t_cmd *current_cmd, t_manager *manager);
int 		close_fds(t_cmd *current_cmd, int *previous_fd, t_manager *manager, 
						int id);
int			execution(t_manager *manager, t_env *s_env);
int			waiting(int id_last);

//exec_heredoc_line
char		**copy_arr(char **to_copy);
t_cmd		*heredoc_line(t_cmd *current_cmd, int *previous_fd, 
							t_manager *manager, int *err_flag);
t_cmd		*heredoc_loop(t_cmd *current_cmd, int *previous_fd, 
							t_manager *manager, char **to_execute);
int			exec_heredoc(t_manager *manager, t_env *s_env, int *previous_fd, 
							t_cmd **current_cmd);


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

//expand heredoc
char    *expand_line(char *current_line, int *i, t_env  *s_env);
char	*expand_heredoc(char *current_line, t_env *s_env);

//fill_cmd_args
int			count_args(t_token *current);
char		**allocate_args(int cmd_count);
t_token		*fill_args_values(t_token *current, char **args, int cmd_count, t_manager *manager);
t_token		*fill_args(t_token *current, t_cmd *cmd, t_manager *manager);


//fill_cmd_expand
int			exploop_env_var(t_token *current_token, t_env *s_env, t_manager *manager);
int			exploop_dquote(t_token *current_token, t_env *s_env, t_manager *manager);
int			expand_loop(t_token *current_token, t_env *s_env, t_manager *manager);

//fill_cmd
int			redir_loop(t_token *current_token, t_cmd *cmd, t_manager *manager);
t_token		*cmd_loop(t_token *current_token, t_cmd *cmd, t_manager *manager);
int			fill_cmd(t_manager *manager, t_env *s_env);
int			redir_in_out(t_token *current_token, t_cmd *cmd, t_manager *manager);

//free_manager
void		free_token(t_token *token);
void		free_export(t_export *export);
void		free_cmd(t_cmd *cmd);
void		free_manager(t_manager *manager);
void		free_env(t_env *env);

//free
// int			closing(t_cmd *cmd, int *previous_fd, t_manager *manager);
void		free_path(char **paths);
int			unlink_heredoc(t_manager *manager);
void		free_cmd_args(char **args);

//handle_files
int			check_heredoc(t_manager *manager);
int			check_infile(char *infile, t_manager *manager);
int			check_outfile(char *outfile, t_manager *manager, t_cmd *cmd, int flag_exec);
int			create_doc(t_manager *manager, int *previous_fd, 
						t_cmd *current_cmd, t_env *s_env);
int			create_doc_loop(int *previous_fd, t_manager *manager, 
						t_cmd *current_cmd, t_env *s_env);

//oplist_manager
t_manager	*init_manager(t_manager *manager, t_env *first_env, int exitcode, t_export *first_export);

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
int			get_size_lim(char *limiter);
int			check_lim(char *limiter, int i);
char		*fill_lim(char *limiter, t_manager *manager, int i);
int			parse_lim(t_token *current_token, t_cmd *cmd, t_manager *manager);
int			heredoc_quotes(char *line, int i, t_manager *manager);


//parsing_spaces_symbols
int			only_space(char *str);
int			is_symbols(char c);
int			only_space_symbols(char *str);
int			skip_spaces(char *line, int i, int *prec_space);

//parsing_operators
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
int			handle_env_pars(t_manager *manager, char *line, int i);
int			sec_type_quotes_cmd(t_manager *manager, char *line, int i);

//parsing
int			handle_parsing_errors(t_manager *manager, char *line);
int			process_token(t_manager *manager, char *line, int i); 
int			parsing(t_manager *manager, char *line);
int			token_error(t_manager *manager);
int			check_redir(t_token *token_tour, t_manager *manager);

#endif