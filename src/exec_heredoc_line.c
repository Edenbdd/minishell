/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:44:09 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/23 15:27:45 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Handling the execution of 1 cmd followed by multiple heredocs*/

#include "minishell.h"
#include "libft.h"

int	exec_heredoc(t_manager *manager, t_env *s_env, int *previous_fd, t_cmd *current_cmd)
{
	int	err_flag;

	err_flag = 0;
	if (!manager->heredoc_line && 
		handle_heredoc(manager, current_cmd, previous_fd, s_env) == -1)
		return (-1);
	if (current_cmd->heredoc_count == 1
		&& !ft_strcmp(current_cmd->args[0], "\n"))
	{
		if (close_fds(current_cmd, previous_fd, manager) == -1)
			return (-1);
		current_cmd = current_cmd->next;
		return (0);
	}
	if (manager->heredoc_line == 1)
	{
		current_cmd = heredoc_line(current_cmd, previous_fd, manager, &err_flag);
		if (err_flag == -1)
			return (-1);
		manager->heredoc_line = 0;
		return (0);
	}
	return (1);
}

char	**copy_arr(char **to_copy)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (to_copy[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (to_copy[i])
	{
		result[i] = ft_strdup(to_copy[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}
t_cmd	*heredoc_loop(t_cmd *current_cmd, int *previous_fd, t_manager *manager, char **to_execute)
{
	t_cmd	*save_last;
	
	while (current_cmd && current_cmd->lim
			&& (!ft_strcmp(to_execute[0], current_cmd->args[0])
			|| !ft_strcmp(current_cmd->args[0], "\n")))
	{
		if (handle_heredoc(manager, 
				current_cmd, previous_fd, manager->env_first) == -1)
			return (NULL);
		save_last = current_cmd;
		current_cmd = current_cmd->next;
	}
	return (save_last);
}


t_cmd	*heredoc_line(t_cmd *current_cmd, int *previous_fd, t_manager *manager, int *err_flag)
{
	int		id;
	char 	**to_execute;

	if (ft_strcmp(current_cmd->args[0], "\n"))
		to_execute = copy_arr(current_cmd->args);
	else
		to_execute = NULL;
	current_cmd = heredoc_loop(current_cmd, previous_fd, manager, to_execute);
	if (!current_cmd)
		return (*err_flag = -1, NULL);
	id = setup_pipe_and_fork(current_cmd, manager);
    if (id == -1)
		return (*err_flag = -1, NULL);
    if (id == 0
		&& child_process(current_cmd, previous_fd, manager, to_execute) == -1)
    		return (*err_flag = -1, NULL);
	free_cmd_args(to_execute);
	close_fds(current_cmd, previous_fd, manager);
	current_cmd = current_cmd->next;
	wait(NULL);
    manager->heredoc_line = 0;
	return (current_cmd);
}
