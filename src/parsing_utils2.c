/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:58:50 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/05 13:55:56 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parsing utils function dealing with redirections token

#include "minishell.h"
#include "libft.h"

int	handle_redir(t_manager *manager, char *line, int i, char **word)
{
	int	type;
	
	type = 0;
	while (line[i] && ft_is_space(line[i]))
		i++;
	i = verif_operator(manager, line, i, &type);
	if (type == DOUBLE_QUOTE)
		i = handle_quote(line, i, type, word);
	if (type == SIMPLE_QUOTE)
		i = handle_quote(line, i, type, word);
	else if (type == CMD_ARG)
		i = regular_word(manager, line, i, word);
	return (i);
}