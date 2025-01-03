/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:36 by smolines          #+#    #+#             */
/*   Updated: 2025/01/03 09:12:07 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// parsing : Gère les cas d'erreur dans la ligne d'entrée
int handle_parsing_errors(t_manager *manager, char *line) 
{
    if (line[0] == '\0')
        return (parsing_error(manager, 3, "bash", NULL));
    if (only_space_symbols(line))
        return (-1);
    if ((count_quotes(manager, line, 34, 39) == -1) 
		|| (count_quotes(manager, line, 39, 34) == -1))
        return (-1);
    return (0);
}

// parsing : Gère les parties de chaine en fonction du type
int process_token(t_manager *manager, char *line, int i) 
{
	int	tmp;

    if (manager->type == DOUBLE_QUOTE || manager->type == SIMPLE_QUOTE)
        return (handle_quote(line, i, manager));
    else if (manager->type == REDIR_IN || manager->type == REDIR_OUT ||
             manager->type == REDIR_APPEND || manager->type == REDIR_HEREDOC) //use is redir ici aussi ?
			{
        		if (manager->type == REDIR_APPEND || manager->type == REDIR_HEREDOC)
            		i++;
				tmp = handle_redir(manager, line, i);
				return (tmp);
			} 
	else if (manager->type == PIPE)
        return (handle_pipe(manager, line, i));
    else if (manager->type == DIREC)
	    return (handle_dir(manager, line, i, NULL));
	else if (manager->type == ENV_VAR)
        return (handle_env_pars(manager, line, i));
    else
        return (regular_word(manager, line, i));
}

// A RECOUPER
// Fonction principale de parsing
int parsing(t_manager *manager, char *line) 
{
    int i;
    int prec_space;
    
	i = 0;
	manager->word = NULL;
    if (handle_parsing_errors(manager, line) == -1)
	    return (-1);
	while (i <= ft_strlen(line) && line[i])
	{
        manager->type = 0;
        i = skip_spaces(line, i, &prec_space);
        i = verif_operator(manager, line, i, &(manager->type));
        if (i == -1)
			return (-1);
        i = process_token(manager, line, i);
        if (i == -1)
	    {	return (free(manager->word), -1);}
		if (manager->type == 0)
			manager->type = check_builtin(manager, manager->word);
        token_add_back(&(manager->token_first), token_new(prec_space, manager));
        free(manager->word);
		manager->word = NULL;
    }
    return (0);
}


/*token_error utils*/
int		check_redir(t_token *token_tour, t_manager *manager)
{
	if ((!token_tour->value || only_space(token_tour->value))
		&& (token_tour->type == REDIR_IN
			|| token_tour->type == REDIR_OUT
			|| token_tour->type == REDIR_HEREDOC
			|| token_tour->type == REDIR_APPEND))
	{
		if ((token_tour->next && token_tour->next->type == PIPE) 
			|| (token_tour->prev && token_tour->prev->type == PIPE))
			return (parsing_error_op(manager, 4, '|', 0));
		else 
			return (parsing_error(manager, 2, "bash", ""));
	}
	return (0);
}

//parsing_condition
int token_error(t_manager *manager)
{
	t_token *token_tour;
	t_token last_token;
	int		only_dir;
	int		count;

	only_dir = 0;
	count = 0;
	token_tour = manager->token_first;
	if (manager->token_first->type == PIPE)
		return (parsing_error_op(manager, 4, '|', 0));
	last_token = *(token_last(manager->token_first));
	if (last_token.type == PIPE) 
			return (parsing_error_op(manager, 4, '|', 0));
	while (token_tour)
	{
		if (token_tour->type == DIREC)
			only_dir++;
		count++;
		if (token_tour->next && token_tour->type == REDIR_HEREDOC &&
			token_tour->next->type == REDIR_HEREDOC)
			manager->heredoc_line = 1;
		if (check_redir(token_tour, manager) == -1)
			return (-1);
		if ((token_tour->next) && (token_tour->type == PIPE 
			&& token_tour->next->type == PIPE))
			return (parsing_error_op(manager, 4, '|', 0));
		token_tour = token_tour->next;
	}
	if (only_dir == count)
		return (access_error(manager, 7, manager->token_first->value, "bash"));
	return (0);
}