/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:22:35 by smolines          #+#    #+#             */
/*   Updated: 2024/12/02 13:20:23 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int parsing_error(t_manager *manager, int code)
{
	if (code == 1)
	{
	printf("minishell doesn't support the operator\n");
	if (manager->token_first)
		{
		free_token(&(manager)->token_first);
		manager->exit_status = 2;
		}
	}
	return (-1);
	
}

