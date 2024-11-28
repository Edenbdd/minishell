/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:19:49 by smolines          #+#    #+#             */
/*   Updated: 2024/11/28 13:53:02 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)env;
	
//loop readline basic
	while (1)
	{
		line = readline("~$");
		//ajouter protection + signaux plus tard
		if (!line)
			exit (1);
		else 
			printf("You entered: %s\n", line);
		if (*line) 
			add_history(line);
		if (!ft_strncmp(line, "exit", ft_strlen(line) - 1))
			break;
	}
	return (0);
}