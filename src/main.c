/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:19:49 by smolines          #+#    #+#             */
/*   Updated: 2024/12/07 15:46:23 by aubertra         ###   ########.fr       */
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
	int			exitcode;

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
		if (!ft_strncmp(line, "exit", ft_strlen(line) - 1))
			break;
		if (parsing(&manager, line) == -1)
		{
			continue;
		}
		printf("display de la liste token\n");
		token_display(manager.token_first);
		fill_cmd(&manager, first_env);
		printf("display de la liste cmd\n");
		cmd_display(manager.cmd_first);
		// printf("check if the expand worked: [%s]\n", manager.cmd_first->args[1]);
		exitcode = execution(&manager, first_env); //si diff de 0 j exit? ou je passe a la suite? ou je le stock?
	}
	return (0);
}

//si ligne vide : exit status = 0 "command not found"