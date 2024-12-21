/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/21 12:44:35 by aubertra         ###   ########.fr       */
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

int handle_heredoc(t_manager *manager, t_cmd *current_cmd, int *previous_fd, t_env *s_env)
{
    if (current_cmd->lim)
    {
        if (create_doc(manager, previous_fd, current_cmd, s_env) == -1)
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
	// if (!current_cmd)
	// 	printf("no current cmd in close fds ?\n");
	// if (!current_cmd->pfd[1])
	// 	printf("no current cmd in close fds ?\n");
	if (current_cmd->pfd[1] != -1)
    {
        if (close(current_cmd->pfd[1]) == -1)
            return (open_close_error(manager, 1));
		current_cmd->pfd[1] = -1;
    }
    if ((current_cmd->index >= 1 || current_cmd->heredoc_count > 0) 
			&& *previous_fd != -1)
    {
		// printf("prev is %d\n", *previous_fd);
        if (close(*previous_fd) == -1)
            return (open_close_error(manager, 1));
	}
    *previous_fd = current_cmd->pfd[0];
    return (0);
}

// execution
#include <sys/stat.h>

int execution(t_manager *manager, t_env *s_env)
{
    t_cmd 	*current_cmd;
    int 	id;
    int 	previous_fd;
    
	previous_fd = -1;
    current_cmd = manager->cmd_first;
    while (current_cmd)
    {
		if (!manager->heredoc_line)
		{
        	if (handle_heredoc(manager, 
				current_cmd, &previous_fd, s_env) == -1)
		    	return (-1);
		}
		if (current_cmd->heredoc_count == 1
			 && !ft_strcmp(current_cmd->args[0], "\n"))
		{
			printf("coming at the right place\n");
			if (close_fds(current_cmd, &previous_fd, manager) == -1)
				return (-1);
			id = 0;
			current_cmd = current_cmd->next;
			continue;
		}
		if (manager->heredoc_line == 1)
		{
			current_cmd = heredoc_line(current_cmd, &previous_fd, manager);
			id = 0;
			manager->heredoc_line = 0;
			continue;
		}
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
    }
	if (previous_fd != -1)
	{
		if (close(previous_fd) == -1)
			return (-1);
	}
	if (unlink_heredoc(manager) == -1)
		return (-1);
	printf("I go into the waiting\n");
    return (waiting(id));
}

static char	**copy_arr(char **to_copy)
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
	printf("i is %d\n", i);
	result[i] = NULL;
	printf("result 0 is [%s], result 1 is [%s]\n", result[0], result[1]);
	return (result);
}

t_cmd	*heredoc_line(t_cmd *current_cmd, int *previous_fd, t_manager *manager)
{
	char 	*path;
	char	**env_arr;
	int		id;
	char 	**to_execute;
	t_cmd	*save_last;

	printf("coming into heredoc line?\n");
	if (ft_strcmp(current_cmd->args[0], "\n"))
	{
		printf("I fill to execute\n");
		to_execute = copy_arr(current_cmd->args);
		printf("to execute 0 is [%s]\n", to_execute[0]);
	}
	while (current_cmd && current_cmd->lim 
			&& (!ft_strcmp(to_execute[0], current_cmd->args[0])
			|| !ft_strcmp(current_cmd->args[0], "\n")))
	{
		if (handle_heredoc(manager, 
				current_cmd, previous_fd, manager->env_first) == -1)
	    {
			printf("pb in heredocline handle\n");
			return (NULL);
		}
		printf("after handle heredoc, prev is %d\n", *previous_fd);
		save_last = current_cmd;
		current_cmd = current_cmd->next;
	}
	current_cmd = save_last;
	printf("before end of heredocline, prev is %d\n", *previous_fd);
	printf("heredocline done\n");
	if (pipe(current_cmd->pfd) == -1)
	{
		printf("pb with the pipe in heredocline\n");
	    return (NULL);
	}
	id = fork();
	if (id == -1)
	{
		printf("fork failed\n");
		return (NULL);
	}
	if (id == 0)
	{
		printf("just before child prev is %d\n", *previous_fd);
		if (dup2(*previous_fd, STDIN_FILENO) == -1)
		{
			printf("pb with dup2 in heredocline\n");
			return (NULL);
		}
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
		printf("going to excve\n");
    	if (execve(path, to_execute, env_arr) == -1)
		{
			printf("pb execve in hereline\n");
        	return (NULL);
		}
	}
	free_cmd_args(to_execute);
	printf("first wait\n");
	close_fds(current_cmd, previous_fd, manager);
	current_cmd = current_cmd->next;
	wait(NULL);
	printf("child wait is done\n");
	return (current_cmd);
}

int	waiting(int id_last)
{
	int	status;
	int	retcode;

	retcode = 0;
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
