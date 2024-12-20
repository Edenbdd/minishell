/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:22:35 by smolines          #+#    #+#             */
/*   Updated: 2024/12/20 14:17:32 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


/*
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
*/


//child process : Gestion des redirections d'entrée

int handle_input_redirection(t_cmd *cmd, int *previous_fd)
{
    if (cmd->infile && !cmd->heredoc_count)
        *previous_fd = open(cmd->infile, O_RDONLY);
    dup2(*previous_fd, STDIN_FILENO);
    return 0;
}

//child process : Gestion des redirections de sortie

int handle_output_redirection(t_cmd *cmd)
{
    if (cmd->append == 1 && cmd->outfile)
        cmd->pfd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (cmd->outfile)
        cmd->pfd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->pfd[1] == -1)
        return -1;
    dup2(cmd->pfd[1], STDOUT_FILENO);
    return 0;
}


int child_process(t_cmd *cmd, int *previous_fd, t_env *s_env, t_manager *manager)
{
    char *path;
    char **env_arr;

    if (cmd->infile || cmd->index != 0 || cmd->heredoc_count)
        handle_input_redirection(cmd, previous_fd);
    if (cmd->outfile || (cmd->index + 1) != manager->size_cmd)
    {
        if (handle_output_redirection(cmd) == -1)
            return (open_close_error(manager, 1));
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
