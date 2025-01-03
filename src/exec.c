/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/03 09:16:12 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Everything related to the execution

#include "minishell.h"
#include "libft.h"

//Execution : Gestion du heredoc
int handle_heredoc(t_manager *manager, t_cmd *current_cmd, int *previous_fd, t_env *s_env)
{
    if (current_cmd->lim)
    {
        printf("coming in the if and current_lim is [%s]\n", current_cmd->lim);
        if (create_doc(manager, previous_fd, current_cmd, s_env) == -1)
            return (-1);
    }
    return (0);
}

//Execution : Gestion des pipes et fork
int setup_pipe_and_fork(t_cmd *current_cmd, t_manager *manager)
{
    if (manager->size_cmd > 1 || manager->heredoc_line == 1)
    {
        if (pipe(current_cmd->pfd) == -1)
            return (system_function_error(manager, 3));
    }
    int id = fork();
    if (id == -1)
        return (system_function_error(manager, 4));
    return id;
}

//Execution : Gestion de la fermeture des fichiers
int close_fds(t_cmd *current_cmd, int *previous_fd, t_manager *manager, int id)
{
	int i;
    struct stat buf;

    //see if this is better than the previous method -> seems great right now
    // printf("prev is %d\n", *previous_fd);
    if ((current_cmd->index >= 1 || current_cmd->heredoc_count > 0) 
			&& *previous_fd != -1)
    {
        if (close(*previous_fd) == -1)
            return (system_function_error(manager, 1));
	}
    *previous_fd = current_cmd->pfd[0];
    i = 3;
    while (i <= 1000)
    {
        if (id == 0)
        {
            if (!fstat(i, &buf))
                close(i);
        }
        else
        {
            if (i != *previous_fd && !fstat(i, &buf))
                close(i);
        }
        i++;
    }
    return (0);
}

// A RECOUPER !!!
int execution(t_manager *manager, t_env *s_env)
{
    t_cmd 	*current_cmd;
    int 	id;
    int 	previous_fd;
    struct stat buf;
    int     check_child;

	previous_fd = -1;
    current_cmd = manager->cmd_first;
    while (current_cmd)
    {
		id = exec_heredoc(manager, s_env, &previous_fd, &current_cmd);
		if (id == -1)
            return (-1);
		else if(id == 0)
        {
            if (current_cmd)
            {    current_cmd = current_cmd->next;}
        	continue;
        }
        id = setup_pipe_and_fork(current_cmd, manager);
        if (id == -1)
            return (-1);
        if (id == 0 )
        {
            check_child = child_process(current_cmd, &previous_fd, manager, NULL);
            if (check_child == -1)
                return (-1);
            else if (check_child == 1)
                continue;
        }
        if (close_fds(current_cmd, &previous_fd, manager, id) == -1)
            return (system_function_error(manager, 1));
        current_cmd = current_cmd->next;
    }
	if (previous_fd != -1 && close(previous_fd) == -1 
        && !fstat(previous_fd, &buf))  
        return (system_function_error(manager, 1));
    if (unlink_heredoc(manager) == -1)
        return (system_function_error(manager, 1));
    return (waiting(id));
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

/*Function before being cut into 2 in case of bug*/
// execution
// int execution(t_manager *manager, t_env *s_env)
// {
//     t_cmd 	*current_cmd;
//     int 	id;
//     int 	previous_fd;
    
// 	previous_fd = -1;
//     current_cmd = manager->cmd_first;
//     while (current_cmd)
//     {
// 		if (!manager->heredoc_line && 
// 			handle_heredoc(manager, current_cmd, &previous_fd, s_env) == -1)
// 		    	return (-1);
// 		if (current_cmd->heredoc_count == 1  //a exterioriser
// 			 && !ft_strcmp(current_cmd->args[0], "\n"))
// 		{
// 			if (close_fds(current_cmd, &previous_fd, manager) == -1)
// 				return (-1);
// 			id = 0;
// 			current_cmd = current_cmd->next;
// 			continue;
// 		}
// 		if (manager->heredoc_line == 1) // a exterioriser
// 		{
// 			current_cmd = heredoc_line(current_cmd, &previous_fd, manager);
// 			id = 0;
// 			manager->heredoc_line = 0;
// 			continue;
// 		}
// 		id = setup_pipe_and_fork(current_cmd, manager);
//         if (id == -1)
//             return (-1);
//         if (id == 0 
// 			&& child_process(current_cmd, &previous_fd, manager, NULL) == -1)
//             return (-1);
//         if (close_fds(current_cmd, &previous_fd, manager) == -1)
//             return (-1);
//         current_cmd = current_cmd->next;
//     }
// 	if (previous_fd != -1 && close(previous_fd) == -1)
// 			return (-1);
// 	if (unlink_heredoc(manager) == -1)
// 		return (-1);
//     return (waiting(id));
// }