/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:36 by smolines          #+#    #+#             */
/*   Updated: 2024/12/30 13:33:42 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//Identify the operator
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
		return (DIREC);
	return (CMD_ARG);
}

//Check for operators that we won't handle
int check_operator_err(t_manager *manager, char *line, int i)
{
	if ((line[i] == '&' && line[i + 1] == '&')
		|| (line[i] == ';') 
		|| (line[i] == '#') 
		|| (line[i] == '\\')
		)
		return (parsing_error_op(manager, 4, line[i], 0));
	if ((line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		|| (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>'))
			return (parsing_error_op(manager, 4, line[i], line[i + 1]));
	return (0);
}

//Handle double operators
int	verif_operator(t_manager *manager, char *line, int i, int *type)
{
	int	result;

	result = is_operators(manager, line, i);
	if 	(result == -1)
			return (-1);
	else if (result != -1)
	{
		*type = result;
		if (result != DIREC && result != PIPE && result != CMD_ARG)
			i++;
	}
	return (i);
}
