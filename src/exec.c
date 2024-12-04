/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/04 13:42:29 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Everything related to the execution

#include "minishell.h"
#include "libft.h"



void	exec_cmd(t_manager *manager, t_env *s_env)
{
	t_token	*current_token;
	t_token	*first_token;

	current_token = manager->token_first;
	while (current_token)
	{
		first_token = current_token;
		while (current_token && current_token->type != PIPE) //expand jusqu au pipe
		{
			//gere les expand en dehors et dans les dquote
			if (current_token->type == ENV_VAR)
				expand(current_token, s_env);
			else if (current_token->type == DOUBLE_QUOTE)
				expand_dquote(current_token, s_env);
			current_token = current_token->next; //skip ce qui n est pas une commande
		}
		//remplir la struct cmd avc cmd et arg et redirs
		while (first_token && first_token->type == CMD_ARG)
		{
			
		}
		if (current_token && current_token->type == PIPE)
			current_token = current_token->next;
	}
}