/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:58:50 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/10 10:58:55 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parsing utils function dealing with redirections token

#include "minishell.h"
#include "libft.h"

int	handle_redir(t_manager *manager, char *line, int i, char **word)
{
	int	type;
	
	type = 0;
	while (line[i] && ft_is_space(line[i]))
		i++;
	i = verif_operator(manager, line, i, &type);
	if (type == DOUBLE_QUOTE)
		i = handle_quote(line, i, type, word);
	if (type == SIMPLE_QUOTE)
		i = handle_quote(line, i, type, word);
	else if (type == CMD_ARG)
		i = regular_word(manager, line, i, word);
	else 
		return (-1)	;
	return (i);
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
			return (parsing_error_op(manager, 4, '|', 0)); //ok
	last_token = *(token_last(manager->token_first));
	if (last_token.type == PIPE) 
			return (parsing_error_op(manager, 4, '|', 0)); //ok
	while (token_tour)
	{
//	printf("hello\n");
		if ((token_tour->type == REDIR_IN && !token_tour->value)
		|| (token_tour->type == REDIR_OUT && token_tour->value == NULL)
		|| (token_tour->type == REDIR_HEREDOC && token_tour->value == NULL)
		|| (token_tour->type == REDIR_APPEND && token_tour->value == NULL))
		{
			if ((token_tour->next && token_tour->next->type == PIPE) 
				|| (token_tour->prev && token_tour->prev->type == PIPE))
					return (parsing_error_op(manager, 4, '|', 0)); //ok
			else 
				return (parsing_error(manager, 2)); //ok
		}
		if ((token_tour->next) && (token_tour->type == PIPE && token_tour->next->type == PIPE))
			return (parsing_error_op(manager, 4, '|', 0)); //ok
	token_tour = token_tour->next;
	}
return (0);

}
