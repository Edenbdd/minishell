/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/12 10:34:46 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Everything related to the execution

#include "minishell.h"
#include "libft.h"

/*
int	execution(t_manager *manager, t_env *s_env)
{
	t_cmd	*current_cmd;
	int		id;
	int		previous_fd;

	previous_fd = -1;
	current_cmd = manager->cmd_first;
	while (current_cmd)
	{
		// printf("parent cmd here: [%s]\n", current_cmd->args[0]);
		if (current_cmd->lim)
		{
			if (create_doc(manager, &previous_fd, current_cmd->lim) == -1)
				return (-1);
		}
		if (manager->size_cmd > 1)
		{
			if (pipe(current_cmd->pfd) == -1) 
				return (open_close_error(manager, 3));
		}
		id = fork(); 
		if (id == -1)
				return (open_close_error(manager, 4));
		if (id == 0)
		{
			if (child_process(current_cmd, &previous_fd, s_env, manager) == -1)
				return (-1);
		}
		if (current_cmd->pfd[1] != -1)
		{
			if (close(current_cmd->pfd[1]) == -1)
				return (open_close_error(manager, 1));
		}
		if (current_cmd->index >= 1 && previous_fd != -1)
		{
			if (close(previous_fd) == -1)
				return (open_close_error(manager, 1));
		}
		previous_fd = current_cmd->pfd[0];
		// printf("PARENT\nprev: %d, cmd->0: %d cmd->1: %d\n", previous_fd, current_cmd->pfd[0], current_cmd->pfd[1]);
		current_cmd = current_cmd->next;
		unlink_heredoc(manager);
	}
	// if (previous_fd != -1)
	// {
	// 	if (close(previous_fd) == -1)
	// 		return (open_close_error(manager, 1));
	// }
	// printf("prev is %d\n", previous_fd);
	return (waiting(id));
}
*/

//Execution : Gestion du heredoc

int handle_heredoc(t_manager *manager, t_cmd *current_cmd, int *previous_fd)
{
    if (current_cmd->lim)
    {
        if (create_doc(manager, previous_fd, current_cmd->lim) == -1)
            return (-1);
    }
    return (0);
}

//Execution : Gestion des pipes et fork

int setup_pipe_and_fork(t_cmd *current_cmd, t_manager *manager)
{
    if (manager->size_cmd > 1)
    {
        if (pipe(current_cmd->pfd) == -1)
            return (open_close_error(manager, 3));
    }
    int id = fork();
    if (id == -1)
        return (open_close_error(manager, 4));
    return id;
}

//Execution : Gestion de la fermeture des fichiers

int close_fds(t_cmd *current_cmd, int *previous_fd, t_manager *manager)
{
    if (current_cmd->pfd[1] != -1)
    {
        if (close(current_cmd->pfd[1]) == -1)
            return (open_close_error(manager, 1));
    }
    if (current_cmd->index >= 1 && *previous_fd != -1)
    {
        if (close(*previous_fd) == -1)
            return (open_close_error(manager, 1));
    }
    *previous_fd = current_cmd->pfd[0];
    return (0);
}

// execution

int execution(t_manager *manager, t_env *s_env)
{
    t_cmd *current_cmd;
    int id;
    int previous_fd;

    previous_fd = -1;
    current_cmd = manager->cmd_first;
    while (current_cmd)
    {
        if (handle_heredoc(manager, current_cmd, &previous_fd) == -1)
            return (-1);

        id = setup_pipe_and_fork(current_cmd, manager);
        if (id == -1)
            return (-1);

        if (id == 0)
        {
            if (child_process(current_cmd, &previous_fd, s_env, manager) == -1)
                return (-1);
        }

        if (close_fds(current_cmd, &previous_fd, manager) == -1)
            return (-1);

        current_cmd = current_cmd->next;
        unlink_heredoc(manager);
    }
    return (waiting(id));
}





int	waiting(int id_last)
{
	int	status;
	int	retcode;

	while (ECHILD != errno)
	{
		if (waitpid(-1, &status, 0) == id_last)
		{
			if (WIFEXITED(status))
				retcode = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				retcode = WTERMSIG(status);
				if (retcode != 131)
					retcode += 128;
			}
		}
	}
	return (retcode);
}
