/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:30:11 by smolines          #+#    #+#             */
/*   Updated: 2024/11/29 13:18:07 by smolines         ###   ########.fr       */
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
t_token	*token_new(char *word, int type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = ft_strdup(word);
	new_token->type = type;
	new_token->flag = 0;
	new_token->next = NULL;
	new_token->prev = NULL;
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
	}
	if (!(*token))
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

void	token_display(t_token *token)
{
	if (token == NULL)
		return ;
	while (token)
	{
		printf("token value :[%s] -- type : [%d]\n", token->value, token->type);
		token = token->next;
	}
}
