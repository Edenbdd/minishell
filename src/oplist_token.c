/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:30:11 by smolines          #+#    #+#             */
/*   Updated: 2024/11/28 22:31:47 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//operations sur la liste token


//ajouter le nouveau token a la liste token
void	*add_new_node(t_token *new_token, t_token **token)
{
	if (!new_token)
		return (NULL);
	ft_lstadd_back(&(*token), new_token);
	return (new_token);
}

//creer un nouveau token
t_token	*ft_lstnew(char *word, int flag)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = word;
	new_token->type = flag;
	new_token->flag = 0;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

// ajouter un nouveau token a la fin de la liste token
void	ft_lstadd_back(t_token **token, t_token *new_token)
{
	t_token	*lastposition;

	if (!new_token)
		return ;
	if (*token)
	{
		lastposition = ft_lstlast(*token);
		lastposition->next = new_token;
	}
	if (!(*token))
		*token = new_token;		
}

// trouver le dernier element de la liste token
t_token	*ft_lstlast(t_token *token)
{
	if (token == NULL)
		return (0);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

