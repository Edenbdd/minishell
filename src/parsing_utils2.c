/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:58:50 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/19 11:44:49 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parsing utils function dealing with redirections token

#include "minishell.h"
#include "libft.h"

/*
int	handle_redir(t_manager *manager, char *line, int i)
{

	manager->sec_type = 0;
	if (manager->type == REDIR_IN && line[i] == '>')
		return (parsing_error(manager, 2));
	if (manager->type == REDIR_OUT && line[i] == '<')
		return (parsing_error_op(manager, 4, '<', 0));
	while (line[i] && ft_is_space(line[i]))
		i++;
	i = verif_operator(manager, line, i, &(manager->sec_type));
	// printf("new type is %d\n", manager->sec_type);
	if (manager->sec_type == DOUBLE_QUOTE)
		i = handle_quote(line, i, manager);
	else if (manager->sec_type == SIMPLE_QUOTE)
		i = handle_quote(line, i, manager);
	else if (manager->sec_type == CMD_ARG)
		i = regular_word(manager, line, i);
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
	else
		return (-1);
	return (i);
}
*/

/*handle secondary type of the files or the following quotes, fill
manager->word accordingly*/
int handle_secondary_type(t_manager *manager, char *line, int i)
{
	printf("sec type is %d\n", manager->sec_type);
    if (manager->sec_type == DOUBLE_QUOTE || manager->sec_type == SIMPLE_QUOTE)
	{
		printf("going in handle sec type\n");
		if (manager->type == REDIR_HEREDOC)
			return (heredoc_quotes(line, i, manager));
		else
			return (handle_quote(line, i - 1, manager));
	}
	else if (manager->sec_type == CMD_ARG)
	{
		if (manager->type == REDIR_HEREDOC &&
			(count_quotes(manager, &line[i], '\'', '"') > 0
			|| count_quotes(manager, &line[i], '"', '\'') > 0))
		{
			printf("coming here\n");
			return (heredoc_quotes(line, i, manager));
		}
		else
		{
			printf("still coming here\n");
	    	return (regular_word(manager, line, i));
		}
	}
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
    return -1;
}
/*Handle redirection operators errors & get the following word 
which is a file or a limiter with handle_secondary_type. 
It will fill manager->word and return i's position after the word*/
int handle_redir(t_manager *manager, char *line, int i)
{
    manager->sec_type = 0;
    if (manager->type == REDIR_IN && line[i] == '>')
        return (parsing_error(manager, 2));
    if (manager->type == REDIR_OUT && line[i] == '<')
        return (parsing_error_op(manager, 4, '<', 0));
    while (line[i] && ft_is_space(line[i]))
	{
        i++;
	}
	printf("r we at h ? [%c] with i %d\n", line[i], i);
    i = verif_operator(manager, line, i, &(manager->sec_type));
	int ret = handle_secondary_type(manager, line, i);
	printf("ret in handle redir from handle sec type is [%d]\n", ret);
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

int	is_an_expand(char *line, int i)
{
	while (line[i] && !ft_is_space(line[i]))
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int handle_env_pars(t_manager *manager, char *line, int i)
{
	if (line[i - 1] == '$' && (line[i] == '\0' || ft_is_space(line[i])))
	{
		manager->type = CMD_ARG;
		manager->word = ft_strdup("$\0");
	}
	else 
		i = regular_word(manager, line, i);
	return (i);
}
