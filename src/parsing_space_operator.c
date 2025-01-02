/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_space_operator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:36 by smolines          #+#    #+#             */
/*   Updated: 2024/12/19 14:26:56 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_symbols(char c)
{
	if (c == ':' || c == '!')
		return (1);
	return (0);
}

int	only_space_symbols(char *str)
{
	while (*str)
	{
		if (!ft_is_space(*str) && !is_symbols(*str))
			return (0);
		str++;	
	}
	return (1);
}

int	only_space(char *str)
{
	while (*str)
	{
		if (!ft_is_space(*str))
			return (0);
		str++;	
	}
	return (1);
}

//recuperer un token "operator"
int	is_operators(t_manager *manager, char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (REDIR_HEREDOC);
	if (line[i] == '>' && line[i + 1] == '>')
		return (REDIR_APPEND);
	if (check_operator_err(manager, line, i) == -1)
		return (-1);
	if (line[i] == '<')
		return (REDIR_IN);
	if (line[i] == '>')
		return (REDIR_OUT);
	if (line[i] == '"')
		return (DOUBLE_QUOTE);
	if (line[i] == '\'')
		return (SIMPLE_QUOTE);
	if (line[i] == '|')
		return (PIPE);
	if (line[i] == '$')
		return (ENV_VAR);
	if (is_a_dir(line, i))
		return (DIR);
	return (CMD_ARG); // is 0
}
//recuperer un token "operator" a l'exception de env var pour pouvoir gerer les doubles expands
int	is_operators_wo_expand(t_manager *manager, char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (REDIR_HEREDOC);
	if (line[i] == '>' && line[i + 1] == '>')
		return (REDIR_APPEND);
	if (check_operator_err(manager, line, i) == -1)
		return (-1);
	if (line[i] == '<')
		return (REDIR_IN);
	if (line[i] == '>')
		return (REDIR_OUT);
	if (line[i] == '"')
		return (DOUBLE_QUOTE);
	if (line[i] == '\'')
		return (SIMPLE_QUOTE);
	if (line[i] == '|')
		return (PIPE);
	if (is_a_dir(line, i))
		return (DIR);
	return (CMD_ARG); // is 0
}


//checker les operateurs non geres
int check_operator_err(t_manager *manager, char *line, int i)
{
//si >>> et plus regarder les messages d'erreur specifiques. idem autres operateurs
	if ((line[i] == '&' && line[i + 1] == '&')
		|| (line[i] == ';') 
		|| (line[i] == '#') 
		|| (line[i] == '\\')
		)
			return (parsing_error_op(manager, 4, line[i], 0)); //ok
	if ((line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		|| (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>'))
			return (parsing_error_op(manager, 4, line[i], line[i + 1])); //ok
	return (0);
}

//recuperer les doubles operateurs
int	verif_operator(t_manager *manager, char *line, int i, int *type)
{
	int	result;

	result = is_operators(manager, line, i);
	if 	(result == -1)
			return (-1);
	else if (result)
	{
		*type = result;
		if (result != DIR && result != PIPE)
			i++;
	}
	return (i);
}
