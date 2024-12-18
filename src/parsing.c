/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:36 by smolines          #+#    #+#             */
/*   Updated: 2024/12/18 18:39:32 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
//parser la chaine de caractere saisie
int	parsing(t_manager *manager, char *line)
{
	int		i;
	int		prec_space;

	i = 0;
	manager->word = NULL;
	if (line[0] == '\0')
		return (parsing_error(manager, 3)); //ok
	if (only_space_symbols(line))
		return (-1);
	if ((count_quotes(manager, line, 34, 39) == -1) || (count_quotes(manager, line, 39, 34) % 2 == -1))
		return (-1);
	while (line[i])
	{
		manager->type = 0;
		prec_space = 0;
		while (line[i] && ft_is_space(line[i]))
		{
			prec_space++;
			i++;
		}
		i = verif_operator(manager, line, i, &(manager->type));
		// printf("type is %d i is %d, line[i] %c\n", manager->type, i, line[i]);
		if (i == -1)
			return (-1);
		if (manager->type == DOUBLE_QUOTE || manager->type == SIMPLE_QUOTE)
			i = handle_quote(line, i, manager);
		else if (manager->type == REDIR_IN || manager->type == REDIR_OUT 
			|| manager->type == REDIR_APPEND || manager->type == REDIR_HEREDOC)
		{
			if (manager->type == REDIR_APPEND || manager->type == REDIR_HEREDOC)
				i++;
			i = handle_redir(manager, line, i);
		}
		else if (manager->type == PIPE)
			i = handle_pipe(manager, line, i);
		else if (manager->type == DIR)
			i = handle_dir(manager, line, i, NULL);
		else if (manager->type == ENV_VAR)
			i = handle_env_pars(manager, line, i);
		else
			i = regular_word(manager, line, i);
		if (i == -1)
			return (free(manager->word), -1);
		token_add_back(&(manager->token_first), token_new(prec_space, manager));
		free(manager->word);
	}
	return (0);
}
*/



// parsing : Gère les cas d'erreur dans la ligne d'entrée
int handle_parsing_errors(t_manager *manager, char *line) 
{
    if (line[0] == '\0')
        return (parsing_error(manager, 3));
    if (only_space_symbols(line))
        return (-1);
    if ((count_quotes(manager, line, 34, 39) == -1) || (count_quotes(manager, line, 39, 34) == -1))
        return (-1);
    return (0);
}

// parsing : Traite les espaces dans la ligne
int skip_spaces(char *line, int i, int *prec_space) 
{
    *prec_space = 0;
    while (line[i] && ft_is_space(line[i])) {
        (*prec_space)++;
        i++;
    }
    return i;
}

// parsing : Gère les parties de chaine en fonction du type
int process_token(t_manager *manager, char *line, int i) 
{
    if (manager->type == DOUBLE_QUOTE || manager->type == SIMPLE_QUOTE)
        return handle_quote(line, i, manager);
    else if (manager->type == REDIR_IN || manager->type == REDIR_OUT ||
             manager->type == REDIR_APPEND || manager->type == REDIR_HEREDOC) 
			{
        		if (manager->type == REDIR_APPEND || manager->type == REDIR_HEREDOC)
            		i++;
        		return handle_redir(manager, line, i);
			} 
	else if (manager->type == PIPE)
        return handle_pipe(manager, line, i);
    else if (manager->type == DIR)
        return handle_dir(manager, line, i, NULL);
    else if (manager->type == ENV_VAR)
        return handle_env_pars(manager, line, i);
    else
        return regular_word(manager, line, i);
}

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
            return (free(manager->word), -1);
        token_add_back(&(manager->token_first), token_new(prec_space, manager));
        free(manager->word);
    }
    return (0);
}

int token_error(t_manager *manager) //a revoir/check
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

//parsing_condition