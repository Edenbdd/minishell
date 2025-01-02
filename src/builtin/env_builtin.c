/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:40:26 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/02 10:55:56 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//mettre les fonctions static dans le .h + trier les fonctions dans des fichiers

void	env_display_builtin(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("%s=%s\n", env->field, env->content);
		env = env->next;
	}
}

int access_error_env(t_manager *manager, int code, char *str)
{
	write(2, "env: ",6);
    write(2, "'", 1);
	ft_putstr_fd(str, 2);
    write(2, "'", 1);
	if (code == 5)
	{
		write (2, ": Permission denied\n", 20);
		manager->exit_status = 1;
	}
	else if (code == 6)
	{
		write(2, ": No such file or directory\n", 28);
		manager->exit_status = 127;			
	}
	else if (code == 7)
	{
		write(2, ": Is a directory\n", 17);
		manager->exit_status = 126;			
	}
	return (-1);
}

int    new_exec(t_manager *manager, t_cmd *cmd, int i)
{
    char    **new_args;
    char    *path;

    path = find_path(cmd->args[i], manager->env_first, manager, 1);
    if (!path)
    {
        if (access(cmd->args[i], F_OK) == -1)
            return (access_error_env(manager, 6, cmd->args[i]));
        if (access(cmd->args[i], X_OK) == -1)
            return (access_error_env(manager, 5, cmd->args[i]));
    }
    new_args = copy_args(cmd->args, i);
    free_cmd_args(cmd->args);
    cmd->args = copy_args(new_args, 0);
    return (0);
}

int    handle_builtin_env(t_manager *manager, t_cmd *cmd)
{
    int i;

    printf("fonction en cours de codage\n");
    i = 0;
    while (cmd->args[i])
    {
        if (ft_strcmp(cmd->args[i], "env"))
        {
            if (new_exec(manager, cmd, i) == -1)
                return (-1);
            print_env(cmd->args);
            if (!check_builtin(manager, cmd->args[0]))
                cmd->is_builtin = 0;            
            return (1);
        }
        i++;
    }
    env_display_builtin(manager->env_first);
    return (0);
}
