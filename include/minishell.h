/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:02:11 by smolines          #+#    #+#             */
/*   Updated: 2024/11/28 13:47:21 by smolines         ###   ########.fr       */
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

typedef struct s_token t_token;
typedef struct s_redirs t_redirs;
typedef struct s_cmd t_cmd;

struct s_token
{
	char	*value;
	char	type;
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
} t_manager;


#endif
