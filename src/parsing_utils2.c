/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:58:50 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/12 13:16:43 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parsing utils function dealing with redirections token

#include "minishell.h"
#include "libft.h"

int	handle_redir(t_manager *manager, char *line, int i, char **word)
{
	int	new_type;
	char op;
	
	new_type = 0;
	op = line[i];
	if (manager->type == REDIR_IN && line[i] == '>')
		return (parsing_error(manager, 2));
	if (manager->type == REDIR_OUT && line[i] == '<')
		return (parsing_error_op(manager, 4, '<', 0));
	while (line[i] && ft_is_space(line[i]))
		i++;
	i = verif_operator(manager, line, i, &new_type);
	// printf("new_type is %d\n", new_type);
	if (new_type == DOUBLE_QUOTE)
		i = handle_quote(line, i, new_type, word);
	if (new_type == SIMPLE_QUOTE)
		i = handle_quote(line, i, new_type, word);
	else if (new_type == CMD_ARG)
		i = regular_word(manager, line, i, word);
	else if (new_type == PIPE)
		return (parsing_error_op(manager, 4, '|', 0));
	else if (new_type == REDIR_OUT)
		return (parsing_error_op(manager, 4, '>', 0));
	else if (new_type == REDIR_APPEND)
		return (parsing_error_op(manager, 4, '>', '>'));
	else if (new_type == REDIR_IN)
		return (parsing_error_op(manager, 4, '<', 0));
	else if (new_type == REDIR_HEREDOC)
		return (parsing_error_op(manager, 4, '<', '<'));
	else
		return (-1);
	return (i);
}

int	handle_pipe(t_manager *manager, char *line, int i, char **word)
{
	if ((i + 1) >= ft_strlen(line))
		return (parsing_error_op(manager, 4, '|', 0));
	if (ft_is_space(line[i + 1]))
	{
		*word = ft_strdup("|");
		return (i);
	}
	else if (ft_isalpha(line[i + 1]))
	{
		*word = ft_strdup("|");
		return (i++);
	}
	else
		return (parsing_error_op(manager, 4, '|', line[i + 1]));
}

// gerer les erreurs dans parsing
// pipe en debit ou fin de chaine
// operateurs multiples separes par whitespaces

int token_error(t_manager *manager)
{
	t_token *token_tour;
	t_token last_token;
	
	token_tour = manager->token_first;
	if (manager->token_first->type == PIPE)
	{
		printf("I come here\n");	
		return (parsing_error_op(manager, 4, '|', 0)); //ok
	}
	last_token = *(token_last(manager->token_first));
	if (last_token.type == PIPE) 
			return (parsing_error_op(manager, 4, '|', 0)); //ok
	while (token_tour)
	{
		if ((token_tour->type == REDIR_IN && !token_tour->value)
		|| (token_tour->type == REDIR_OUT && token_tour->value == NULL)
		|| (token_tour->type == REDIR_HEREDOC && token_tour->value == NULL)
		|| (token_tour->type == REDIR_APPEND && token_tour->value == NULL))
		{
			if ((token_tour->next && token_tour->next->type == PIPE) 
				|| (token_tour->prev && token_tour->prev->type == PIPE))
					{
					// printf("bbb\n\bbb\nbbbbb\n");
					return (parsing_error_op(manager, 4, '|', 0)); //ok
					}
			else 
			{
				// printf("aaa\naaa\naaa\naaa\n");
				return (parsing_error(manager, 2)); //ok
			}
		}
		if ((token_tour->next) && (token_tour->type == PIPE && token_tour->next->type == PIPE))
			return (parsing_error_op(manager, 4, '|', 0)); //ok
	token_tour = token_tour->next;
	}
return (0);
}
