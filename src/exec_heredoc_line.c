/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:44:09 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/21 14:59:41 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Handling the execution of 1 cmd followed by multiple heredocs*/

#include "minishell.h"
#include "libft.h"

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

t_cmd	*heredoc_line(t_cmd *current_cmd, int *previous_fd, t_manager *manager)
{
	char 	*path;
	char	**env_arr;
	int		id;
	char 	**to_execute;
	t_cmd	*save_last;

	if (ft_strcmp(current_cmd->args[0], "\n"))
		to_execute = copy_arr(current_cmd->args);
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
	current_cmd = save_last;
	id = setup_pipe_and_fork(current_cmd, manager);
        if (id == -1)
            return (-1);
    if (id == 0)
    {
        if (child_process(current_cmd, &previous_fd, manager, to_execute) == -1)
            return (-1);
    }
    //CHILD PROCESS A AJUSTER POUR FIT A CE DEROULER
	if (id == 0)
	{
		if (dup2(*previous_fd, STDIN_FILENO) == -1)
			return (NULL);
		if (current_cmd->outfile)
		{
			if (current_cmd->append == 1 && current_cmd->outfile)
        		current_cmd->pfd[1] = open(current_cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    		else if (current_cmd->outfile)
        		current_cmd->pfd[1] = open(current_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    		dup2(current_cmd->pfd[1], STDOUT_FILENO);
		}
		close_fds(current_cmd, previous_fd, manager);
		path = find_path(to_execute[0], manager->env_first, manager);
   		if (path == NULL)
		{
			cmd_error(manager, 6, to_execute[0]);
			free_cmd_args(to_execute);
			return (NULL);
		}
		env_arr = convert_env(manager->env_first);
    	if (execve(path, to_execute, env_arr) == -1)
        	return (NULL);
	}
    //UNTIL HERE!
	free_cmd_args(to_execute);
	close_fds(current_cmd, previous_fd, manager);
	current_cmd = current_cmd->next;
	wait(NULL);
    manager->heredoc_line = 0; //reset pour la suite
	return (current_cmd);
}
