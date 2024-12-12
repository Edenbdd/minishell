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

int	child_process(t_cmd *cmd, int *previous_fd, t_env *s_env, t_manager *manager)
{
	char	*path;
	char	**env_arr;
	// printf("cmd here: [%s]\n", cmd->args[0]);
	// printf("CHILD\nprev: %d, cmd->0: %d cmd->1: %d\n", *previous_fd, cmd->pfd[0], cmd->pfd[1]);
	if (cmd->infile || cmd->index != 0  || cmd->heredoc_priority)
	{
		if (cmd->infile  && !cmd->heredoc_priority)
		{
			*previous_fd = open(cmd->infile, O_RDONLY);
		}
		dup2(*previous_fd, STDIN_FILENO);
	}
	if (cmd->outfile || (cmd->index + 1) != manager->size_cmd)
	{
		if (cmd->append == 1 && cmd->outfile)
			cmd->pfd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (cmd->outfile)
			cmd->pfd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->pfd[1] == -1)
				return (open_close_error(manager, 1));
		dup2(cmd->pfd[1], STDOUT_FILENO);	
	}
	if (closing(cmd, previous_fd, manager) == -1)
		return (-1);
	path = find_path(cmd->args[0], s_env, manager);
	if (path == NULL)
		return (cmd_error(manager, 6, cmd->args[0]));
	env_arr = convert_env(s_env);
	if (execve(path, cmd->args, env_arr) == -1) 
		return (open_close_error(manager, 2));
	return (0);
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