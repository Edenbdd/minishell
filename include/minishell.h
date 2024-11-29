/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:02:11 by smolines          #+#    #+#             */
/*   Updated: 2024/11/29 15:56:07 by smolines         ###   ########.fr       */
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
}   t_token_type;

typedef struct s_token t_token;
typedef struct s_redirs t_redirs;
typedef struct s_cmd t_cmd;
typedef struct s_env t_env;
typedef struct s_export t_export;

struct s_token
{
	char	*value;
	int		type;
	int		flag; //use as a bool i.e. 0 or 1
	t_token	*next;
	t_token	*prev;
};

struct s_cmd
{
	char		*path;
	char		**args;
	pid_t		pid;
	t_redirs	*redir;
	t_cmd		*next;
	t_cmd		*prev;	
};

struct s_redirs
{
	char	*infile;
	int		in_fd;
	char	*outfile;
	int		out_fd;
	int		pfd[2];
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
	char	*field;
	char	*content;
	t_export	*next;
	t_export	*prev;
};


//Moniter/Control/Manager
typedef struct s_manager
{
	t_token		*token_first;
	t_token		*token_last;
	int			size_token;
	t_cmd		*cmd_first;
	t_cmd		*cmd_last;
	int			size_cmd;
	t_redirs	*redirs;
	t_env		*env_first;
	t_env		*env_last;
	int			size_env;
	t_export	*export_first;
	t_export	*export_last;
	int			size_export;
} t_manager;



//parsing
t_manager	*parsing(t_manager *manager,char *line);

//init
t_manager	*init_manager(t_manager *manager);


//Operations sur liste token
void	*token_add_new(t_token *new_token, t_token **token);
t_token	*token_new(char *word, int flag);
void	token_add_back(t_token **token, t_token *new_token);
t_token	*token_last(t_token *token);
void	token_display(t_token *token);

//free
void	free_token(t_token **token);

//error
void parsing_error(t_manager *manager, int code);

//display
void	token_display(t_token *token);

#endif
