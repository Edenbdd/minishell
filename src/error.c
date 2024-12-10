/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:22:35 by smolines          #+#    #+#             */
/*   Updated: 2024/12/10 13:10:30 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	parsing_error_op(t_manager *manager, int code, char operator, char dble_op)
{
	//if (code == 3)
	//{
	//	printf("empty line\n");
	//	if (manager->token_first)
	//		free_token(&(manager)->token_first);
	//	manager->exit_status = 0;			
	//	return (-1);
	//}
		if (code == 4)
	{
		if (dble_op != '0')
			printf("bash : syntax error near unexpected token '%c%c'\n", operator, dble_op);
		else 
			printf("bash : syntax error near unexpected token '%c'\n", operator);
		if (manager->token_first)
			free_token(&(manager)->token_first);
		manager->exit_status = 2;			
		return (-1);
	}
	return (-1);
}
		
	
int parsing_error(t_manager *manager, int code)
{
	if (code == 2)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		if (manager->token_first)
			free_token(&(manager)->token_first);
		manager->exit_status = 2;			
		return (-1);
	}

	if (code == 3)
	{
//		printf("empty line\n");
		if (manager->token_first)
			free_token(&(manager)->token_first);
		manager->exit_status = 127;			
		return (-1);
	}

// avant cette ligne = parties terminees

	//if (code == 1)
	//{
	//	printf("minishell doesn't support the operator\n");
	//	if (manager->token_first)
	//		free_token(&(manager)->token_first);
	//	manager->exit_status = 2;
	//	return (-1);
	//	}
	
	
	if (code == 4)
	{
		printf("bash : syntax error");
		if (manager->token_first)
			free_token(&(manager)->token_first);
		manager->exit_status = 2;			
		return (-1);
	}
	//	if (code == 5)
	//{
	//	printf("bash : Permission denied\n");
	//	if (manager->token_first)
	//		free_token(&(manager)->token_first);
	//	manager->exit_status = 1;			
	//	return (-1);
	//}
return (-1);
}


int access_error(t_manager *manager, int code, char *str)
{
		if (code == 5)
	{
		printf("bash : %s: Permission denied\n", str);
		if (manager->token_first)
			free_token(&(manager)->token_first);
		manager->exit_status = 1;			
		return (-1);
	}
return (-1);
}

int open_close_error(t_manager *manager, int code)
{
		if (code == 1)
	{
		printf("bash: open or close error\n");
		if (manager->token_first)
			free_token(&(manager)->token_first);
		//pas de exit status selon chat gpt	
		return (-1);
	}
return (-1);
}


int cmd_error(t_manager *manager, int code, char *cmd)
{
		if (code == 6)
	{
		printf("bash: %s: command not found\n", cmd);
		if (manager->token_first)
			free_token(&(manager)->token_first);
		manager->exit_status = 127;			
		return (-1);
	}
return (-1);
}

