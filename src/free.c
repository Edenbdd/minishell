/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:00:56 by smolines          #+#    #+#             */
/*   Updated: 2024/12/07 16:19:27 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//fonctions pour free les differentes struct

#include "minishell.h"
#include "libft.h"

void	free_token(t_token **token)
{
	t_token	*tmp;

	if (!token || !(*token))
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		if ((*token)->value)
			free((*token)->value);
		free(*token);
		*token = tmp;
	}
	*token = NULL;
}
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

void	closing(t_cmd *cmd, int *previous_fd)
{
	if (cmd->pfd[1] != -1)
		close(cmd->pfd[1]);
	if (cmd->pfd[0] != -1)
		close(cmd->pfd[0]);
	if (*previous_fd != -1)
		close(*previous_fd);
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
//ici il me faut un free path
//ici il me faut aussi un free manager
//ici il me faut un free env
//ici il me faut un free cmd