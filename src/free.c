/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:00:56 by smolines          #+#    #+#             */
/*   Updated: 2024/12/11 15:43:07 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//fonctions pour free les differentes struct

#include "minishell.h"
#include "libft.h"

void	free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

int	closing(t_cmd *cmd, int *previous_fd, t_manager *manager)
{
	if (cmd->pfd[1] != -1)
	{
		if (close(cmd->pfd[1]) == -1)
			return (open_close_error(manager, 1));
	}
	if (cmd->pfd[0] != -1)
	{
		if (close(cmd->pfd[0]) == -1)
			return (open_close_error(manager, 1));
	}
	if (*previous_fd != -1)
	{
		if (close(*previous_fd) == -1)
			return (open_close_error(manager, 1));
	}
	return (0);
}

void	unlink_heredoc(t_manager *manager)
{
	(void)manager;
	if (!access("heredoc_tmp", F_OK))
	{
		if (unlink("heredoc_tmp") == -1)
			printf("we need an error handling here\n");
	}
}

void	free_cmd_args(char **args)
{
	int	i;
	
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

