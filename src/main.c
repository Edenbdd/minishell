/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:19:49 by smolines          #+#    #+#             */
/*   Updated: 2024/12/03 17:20:25 by smolines         ###   ########.fr       */
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
	while (1)
	{
		init_manager(&manager);
		line = readline("~$");
		//ajouter protection + signaux plus tard
		if (!line)
			continue;
		else 
//			printf("You entered: %s\n", line);
		if (*line) 
			add_history(line);
		if (!ft_strncmp(line, "exit", ft_strlen(line) - 1))
			break;
		if (parsing(&manager, line) == -1)
		{
//			printf("exit status : [%d]\n", manager.exit_status);
			continue ;
		}
		//printf("display de la liste token\n");
		//token_display(manager.token_first);
		exec_cmd(&manager, first_env);
	}
	return (0);
}

//si ligne vide : exit status = 0 "command not found"