/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:19:49 by smolines          #+#    #+#             */
/*   Updated: 2024/12/10 16:44:27 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Only the main here

#include "minishell.h"
#include "libft.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_manager	manager;
	t_env		*first_env;
//	int			exitcode;

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
		if (*line)
			add_history(line);
		// if (!ft_strncmp(line, "exit", ft_strlen(line) - 1))
		// 	break;
		if (parsing(&manager, line) == -1)
			continue;
		if (token_error(&manager) == -1)
			continue ;
//		 printf("display de la liste token\n");
//		 token_display(manager.token_first);
		if (fill_cmd(&manager, first_env) == -1)
			continue;
//		 printf("display de la liste cmd\n");
//		 cmd_display(manager.cmd_first);
		// printf("check if the expand worked: [%s]\n", manager.cmd_first->args[1]);
		manager.exit_status = execution(&manager, first_env); //si diff de 0 j exit? ou je passe a la suite? ou je le stock?
		//if (manager.exit_status == -1)
		//	continue;
		printf("manager.exit_status : [%d]\n", manager.exit_status);
	}
//	free_manager(&manager);
	return (0);
}

//si ligne vide : exit status = 0 "command not found"