/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:19:49 by smolines          #+#    #+#             */
/*   Updated: 2024/12/03 10:26:20 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_manager	manager;
	t_env		*first_env;
	
	(void)argc;
	(void)argv;
	first_env = handle_env(env);
//	env_display(first_env);
//loop readline basic
	while (1)
	{
		init_manager(&manager);
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
		parsing(&manager, line);
		printf("display de la liste token\n");
		token_display(manager.token_first);
		exec_cmd(&manager);
	}
	return (0);
}