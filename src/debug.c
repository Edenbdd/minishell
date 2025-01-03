/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:19 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/02 19:48:28 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Functions used to display tokens & cmd used to debug*/

#include "minishell.h"
#include "libft.h"

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
		token = token->next;
	}
}
void	cmd_display(t_cmd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		printf("arg[0]: [%s]-- infile: [%s]-- lim: [%s] -- append: [%d]-- outfile:[%s]-- builtin ? [%d]\n",cmd->args[0], cmd->infile,  cmd->lim, cmd->append, cmd->outfile, cmd->is_builtin);
		cmd = cmd->next;
	}
}

void	cmd_args_display(t_cmd *cmd)
{
	int i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd->args[i])
	{
		printf("arg[%d]: [%s]\n",i, cmd->args[i]);
		i++;
	}
}


