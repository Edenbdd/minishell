/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:19:49 by smolines          #+#    #+#             */
/*   Updated: 2024/12/11 18:13:11 by aubertra         ###   ########.fr       */
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
		if (!ft_strncmp(line, "stop", 5))
		{
			break;
		}
		if (parsing(&manager, line) == -1)
		{
			continue;
		}
		if (token_error(&manager) == -1)
		{
			printf("token error\n");
			continue ;
		}
		printf("display de la liste token\n");
		token_display(manager.token_first);
		if (fill_cmd(&manager, first_env) == -1)
			continue;
		 printf("display de la liste cmd\n");
		 cmd_display(manager.cmd_first);
		printf("check if the expand worked: [%s]\n", manager.cmd_first->args[1]);
		execution(&manager, first_env);
		free_manager(&manager);
		break;
	}
	free_env(first_env);
	return (0);
}
