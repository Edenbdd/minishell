/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:22:35 by smolines          #+#    #+#             */
/*   Updated: 2025/01/02 10:52:01 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*Child process & handling of input and output redirection*/

//child process : Gestion des redirections d'entrée

int handle_input_redirection(t_cmd *cmd, int *previous_fd, t_manager *manager)
{
    if (cmd->infile && !cmd->heredoc_count 
        && !manager->heredoc_line)
        *previous_fd = open(cmd->infile, O_RDONLY);
    if (*previous_fd != -1)
    {
        if (dup2(*previous_fd, STDIN_FILENO) == -1)
            return (system_function_error(manager, 8));
    }
    return (0);
}

//child process : Gestion des redirections de sortie
int handle_output_redirection(t_cmd *cmd, t_manager *manager)
{
    // printf("for pid [%d] pdf1 is [%d]\n", getpid(), cmd->pfd[1]);
    check_outfile(cmd->outfile, manager, cmd, 1);
    if (cmd->pfd[1] == -1)
        return (-1);
    dup2(cmd->pfd[1], STDOUT_FILENO);
    return (0);
}

int path_execution_heredocline(t_manager *manager, char **to_execute)
{
    char *path;
    char **env_arr;  

    path = find_path(to_execute[0], manager->env_first, manager, 0);
    if (!path)
    {
        cmd_error(manager, to_execute[0], 0);
        free_cmd_args(to_execute);
        return (-1);
    }
    env_arr = convert_env(manager->env_first);
    if (execve(path, to_execute, env_arr) == -1)
        return (-1);
    return (0);
}

//A RECOUPER
//changer les return en exit !
int child_process(t_cmd *cmd, int *previous_fd, t_manager *manager, char **to_execute)
{
    char *path;
    char **env_arr;
    
    path = NULL;
    if (cmd->infile || cmd->index != 0 || cmd->heredoc_count || manager->heredoc_line)
        handle_input_redirection(cmd, previous_fd, manager);
    if (cmd->outfile || (cmd->index + 1) != manager->size_cmd)
    {
        if (handle_output_redirection(cmd, manager) == -1)
            return (system_function_error(manager, 1));
    }
    if (close_fds(cmd, previous_fd, manager, 0) == -1)
        return (system_function_error(manager, 1));
    if (cmd->is_builtin == 1)
        return (builtin_exec_path(manager, cmd, previous_fd));
    if (to_execute &&
            path_execution_heredocline(manager, to_execute) == -1)
        return (system_function_error(manager, 2));
    if (cmd->args && cmd->args[0])
        path = find_path(cmd->args[0], manager->env_first, manager, 0);
    if (path == NULL && cmd->args && cmd->args[0])
        return (cmd_error(manager, cmd->args[0], 1));
    if (path == NULL)
        return (cmd_error(manager, NULL, 1));
    env_arr = convert_env(manager->env_first);
    if (execve(path, cmd->args, env_arr) == -1)
        return (system_function_error(manager, 2));
    return (0);
}

