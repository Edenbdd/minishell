/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:19 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/20 16:52:10 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//trouver le bon chemin associer avec la cmd

#include "minishell.h"
#include "libft.h"

//utile pour le debug only
void		print_env(char **env_arr)
 {
 	int	i;

 	i = 0;
 	while (env_arr[i])
 	{
 		printf("%s\n", env_arr[i]);
 		i++;
 	}
 }

void	token_display(t_token *token)
{
	if (token == NULL)
		return ;
	while (token)
	{
		printf("token value :[%s] -- type : [%d]\n", token->value, token->type);
		//if (token->prev)
		//	printf("        prev_value : [%s]\n", token->prev->value);
		//else
		//	printf("        prev_value : [NULL]\n");
		token = token->next;
	}
}
void	cmd_display(t_cmd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		// printf("is the bug here \n");
		printf("arg[0]: [%s]-- infile: [%s]-- lim: [%s] -- append: [%d]-- outfile:[%s]\n",cmd->args[0], cmd->infile,  cmd->lim, cmd->append, cmd->outfile);
		cmd = cmd->next;
	}
}

