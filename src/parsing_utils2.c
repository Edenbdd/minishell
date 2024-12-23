/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:58:50 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/23 14:40:47 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parsing utils function dealing with redirections token

#include "minishell.h"
#include "libft.h"

/*Utils of handle_secondary_type*/
int	sec_type_quotes_cmd(t_manager *manager, char *line, int i)
{
    if (manager->sec_type == DOUBLE_QUOTE || manager->sec_type == SIMPLE_QUOTE)
	{
		if (manager->type == REDIR_HEREDOC)
			return (heredoc_quotes(line, i - 1, manager));
		else
			return (handle_quote(line, i - 1, manager));
	}
	else
	{
		if (manager->type == REDIR_HEREDOC &&
			(count_quotes(manager, &line[i], '\'', '"') > 0
			|| count_quotes(manager, &line[i], '"', '\'') > 0))
			return (heredoc_quotes(line, i, manager));
		else
	    	return (regular_word(manager, line, i));
	}
}

/*handle secondary type of the files or the following quotes, fill
manager->word accordingly*/
int handle_secondary_type(t_manager *manager, char *line, int i)
{
	if (manager->sec_type == DOUBLE_QUOTE || manager->sec_type == SIMPLE_QUOTE
		|| manager->sec_type == CMD_ARG)
		return (sec_type_quotes_cmd(manager, line, i));
	else if (manager->sec_type == ENV_VAR && manager->type == REDIR_HEREDOC)
		return (heredoc_quotes(line, i - 1, manager));
	else if (manager->sec_type == PIPE)
        return (parsing_error_op(manager, 4, '|', 0));
    else if (manager->sec_type == REDIR_OUT)
        return (parsing_error_op(manager, 4, '>', 0));
    else if (manager->sec_type == REDIR_APPEND)
        return (parsing_error_op(manager, 4, '>', '>'));
    else if (manager->sec_type == REDIR_IN)
        return (parsing_error_op(manager, 4, '<', 0));
    else if (manager->sec_type == REDIR_HEREDOC)
        return (parsing_error_op(manager, 4, '<', '<'));
    return (-1);
}
/*Handle redirection operators errors & get the following word 
which is a file or a limiter with handle_secondary_type. 
It will fill manager->word and return i's position after the word*/
int handle_redir(t_manager *manager, char *line, int i)
{
	int	ret;

    manager->sec_type = 0;
    if (manager->type == REDIR_IN && line[i] == '>')
        return (parsing_error(manager, 2));
    else if (manager->type == REDIR_OUT && line[i] == '<')
        return (parsing_error_op(manager, 4, '<', 0));
	else if (manager->type == REDIR_HEREDOC && only_space(&line[i]))
		return (parsing_error(manager, 2));
    while (line[i] && ft_is_space(line[i]))
        i++;
    i = verif_operator(manager, line, i, &(manager->sec_type));
	ret = handle_secondary_type(manager, line, i);
    return (ret);
}

int	handle_pipe(t_manager *manager, char *line, int i)
{
	if ((i + 1) >= ft_strlen(line))
		return (parsing_error_op(manager, 4, '|', 0));
	else if (ft_isalpha(line[i + 1]) || ft_is_space(line[i + 1]))
	{
		manager->word = ft_strdup("|");
		i++;
		return (i);
	}
	else
	{
		manager->word = NULL;
		return (parsing_error_op(manager, 4, '|', line[i + 1]));
	}
}

int handle_env_pars(t_manager *manager, char *line, int i)
{
	if (line[i - 1] == '$' && (line[i] == '\0' || ft_is_space(line[i])))
	{
		manager->type = CMD_ARG;
		manager->word = ft_strdup("$\0");
	}
	else if (line[i - 1] == '$' && (line[i] == '?'))
		i = expand_errno(manager);
	else 
		i = regular_word(manager, line, i);
	return (i);
}

/*Original function to keep in case of bug in the shortened version*/
// int handle_secondary_type(t_manager *manager, char *line, int i)
// {
//     if (manager->sec_type == DOUBLE_QUOTE || manager->sec_type == SIMPLE_QUOTE)
// 	{
// 		if (manager->type == REDIR_HEREDOC)
// 			return (heredoc_quotes(line, i - 1, manager));
// 		else
// 			return (handle_quote(line, i - 1, manager));
// 	}
// 	else if (manager->sec_type == CMD_ARG)
// 	{
// 		if (manager->type == REDIR_HEREDOC &&
// 			(count_quotes(manager, &line[i], '\'', '"') > 0
// 			|| count_quotes(manager, &line[i], '"', '\'') > 0))
// 			return (heredoc_quotes(line, i, manager));
// 		else
// 	    	return (regular_word(manager, line, i));
// 	}
// 	else if (manager->sec_type == ENV_VAR && manager->type == REDIR_HEREDOC)
// 			return (heredoc_quotes(line, i - 1, manager));
// 	else if (manager->sec_type == PIPE)
//         return (parsing_error_op(manager, 4, '|', 0));
//     else if (manager->sec_type == REDIR_OUT)
//         return (parsing_error_op(manager, 4, '>', 0));
//     else if (manager->sec_type == REDIR_APPEND)
//         return (parsing_error_op(manager, 4, '>', '>'));
//     else if (manager->sec_type == REDIR_IN)
//         return (parsing_error_op(manager, 4, '<', 0));
//     else if (manager->sec_type == REDIR_HEREDOC)
//         return (parsing_error_op(manager, 4, '<', '<'));
//     return (-1);
// }