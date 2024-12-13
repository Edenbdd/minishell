/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:19:49 by smolines          #+#    #+#             */
/*   Updated: 2024/12/13 20:18:22 by aubertra         ###   ########.fr       */
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
	exitcode = 0;
	while (1)
	{
		init_manager(&manager, *first_env, exitcode);
		line = readline("$>");
		//ajouter protection + signaux plus tard
		if (!line)
			continue;
		if (*line)
			add_history(line);
		if (!ft_strncmp(line, "stop", 5))
		{
			exitcode = manager.exit_status;
			free_manager(&manager);
			break;
		}
		if (parsing(&manager, line) == -1)
		{
			exitcode = manager.exit_status;
			free_manager(&manager);
			continue;
		}
		if (token_error(&manager) == -1)
		{
			exitcode = manager.exit_status;
			free_manager(&manager);
			continue ;
		}
		// printf("display de la liste token\n");
		// token_display(manager.token_first);
		if (fill_cmd(&manager, first_env) == -1)
		{
			exitcode = manager.exit_status;
			free_manager(&manager);
			continue;
		}
		// printf("check if the expand worked: [%s]\n", manager.cmd_first->args[1]);
		// printf("exit status [%d]\n", manager.env_first->exit_status);
		// printf("display de la liste cmd\n");
		// cmd_display(manager.cmd_first);
		execution(&manager, first_env);
		exitcode = manager.exit_status;
		free_manager(&manager);
	}
	printf("we exit\n");
	free_env(first_env);
	return (0);
}
