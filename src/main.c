/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:19:49 by smolines          #+#    #+#             */
/*   Updated: 2024/12/27 16:56:40 by aubertra         ###   ########.fr       */
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
			break;
		else if (!ft_strncmp(line, "\n", 1))
			continue;
		if (*line)
			add_history(line);
		// printf("line is [%s]\n", line);
		if (parsing(&manager, line) == -1)
		{
			exitcode = manager.exit_status;
			free_manager(&manager);
			printf("parsing error\n");
			continue;
		}
		if (token_error(&manager) == -1)
		{
			printf("Token_error exit\n");
			exitcode = manager.exit_status;
			free_manager(&manager);
			continue ;
		}
		printf("\033[31mdisplay de la liste token\033[0m\n");
		token_display(manager.token_first);
		if (fill_cmd(&manager, first_env) == -1)
		{
			exitcode = manager.exit_status;
			free_manager(&manager);
			printf("cmd error\n");
			continue;
		}
		// printf("check if the expand worked: [%s]\n", manager.cmd_first->args[1]);
		printf("exit status [%d]\n", manager.exit_status);
		printf("\033[31mdisplay de la liste cmd\033[0m\n");
		// cmd_display(manager.cmd_first);
		if (execution(&manager, first_env) == -1)
		{
			printf("exec error\n");
			exitcode = manager.exit_status;
			free_manager(&manager);
			continue;
		}
		exitcode = manager.exit_status;
		free_manager(&manager);
		// break;
	}
	free_env(first_env);
	return (0);
}
