/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:30:11 by smolines          #+#    #+#             */
/*   Updated: 2024/12/13 17:08:53 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//ajouter le nouveau token a la liste token
void	*token_add_new(t_token *new_token, t_token **token)
{
	if (!new_token)
		return (NULL);
	token_add_back(&(*token), new_token);
	return (new_token);
}

//creer un nouveau token
t_token	*token_new(int prec_space, t_manager *manager)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	if (manager->word)	
		new_token->value = ft_strdup(manager->word);
	else
		new_token->value = NULL;
	new_token->type = manager->type;
	new_token->space = prec_space;
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->nb = 0;
	return (new_token);
}

// ajouter un nouveau token a la fin de la liste token
void	token_add_back(t_token **token, t_token *new_token)
{
	t_token	*lastposition;

	if (!new_token)
		return ;
	if (*token)
	{
		lastposition = token_last(*token);
		lastposition->next = new_token;
		new_token->prev = lastposition;

		new_token->nb = new_token->prev->nb + 1;
	}
	else
		*token = new_token;	
}

// trouver le dernier element de la liste token
t_token	*token_last(t_token *token)
{
	if (token == NULL)
		return (0);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

