/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:32:13 by smolines          #+#    #+#             */
/*   Updated: 2025/01/02 19:39:35 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//utils for several built-in fonctions

#include "minishell.h"
#include "libft.h"


int count_cmd_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while(cmd->args[i])
		i++;
	return (i);
}