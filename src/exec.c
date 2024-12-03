/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/03 16:59:53 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Everything related to the execution

#include "minishell.h"
#include "libft.h"





void	exec_cmd(t_manager *manager, t_env *s_env)
{

	t_token	*current_token;
	printf("exec_cmd debut fonction\n");
	current_token = manager->token_first;
	while(current_token)
	{
		printf("exec_cmd debut 1er while\n");

		while(current_token && current_token->type != PIPE) //parcourir les token
		{
			printf("exec_cmd debut 2eme while\n");

			if (current_token->type == ENV_VAR)
			{
				printf("en var if\n");
				expand(current_token, s_env);
				printf("current token value : [%s]\n", current_token->value);
			}
			if (current_token->type == DOUBLE_QUOTE)
			{
				printf("dquote if\n");
				expand_dquote(current_token, s_env);
				printf("current token value : [%s]\n", current_token->value);
			}
			
			current_token = current_token->next; //skip ce qui n est pas une commande
		}
		if (current_token && current_token->type == PIPE)
			current_token = current_token->next;
	}
}

//void	exec_cmd(t_manager *manager) //parsing token
//{
//	t_token	*current_token;
//	int		counting_cmd;
	
//	current_token = manager->token_first;
//	couting_cmd = 0;
//	//IDENTIFIER LORSAUE REDIRECTION 
//	//remplir la structure cmd pour avoir toutes les infos 
//	while(current_token) //parcourir les token
//	{
//		if (current_token->type == CMD_ARG) //premiere cmd rempli la struct
//			fill_cmd(current_token, manager->cmd_first);
//		while (current_token->type == CMD_ARG) //skip les arg de la cmd (deja dans la struct)
//			current_token = current_token->next;
//		//ENTRE LES CMD ON A DES PIPES
//		current_token = current_token->next; //skip ce qui n est pas une commande
//	}
//	//ensuite executer chaque cmd dans un child different (si pipe)
//	//pour l instant executer une seule cmd
//}