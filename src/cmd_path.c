/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:19 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/23 15:08:30 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*trouver le bon chemin associer avec la cmd*/

#include "minishell.h"
#include "libft.h"

char	*get_path(t_env *s_env)
{
	t_env	*current;

	current = s_env;
	while (current)
	{
		if (!ft_strcmp(current->field, "PATH"))
			break ;
		current = current->next;
	}
	return (current->content);
}

char	*find_path(char *cmd, t_env *s_env, t_manager *manager)
{
	char	**paths;
	char	*right_path;

	(void)manager;
	if (!cmd || !cmd[0]) 
		return (NULL);
	if (!s_env || cmd[0] == '.' || cmd[0] == '/')
		return (absolute_path(cmd, manager));
	paths = ft_split(get_path(s_env), ':');
	if (!paths) 
		return (NULL);
	right_path = test_path(paths, cmd, manager);
	free_path(paths);
	if (!right_path)
		return (NULL);
	return (right_path);
}

char	*join_path(char *path, char *cmd, t_manager *manager, char **paths)
{
	char	*tmp;
	char	*to_test;

	(void)manager;
	tmp = ft_strjoin(path, "/");
	if (!tmp)
	{
		free_path(paths);
		return (NULL);
	}
	to_test = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!to_test)
	{
		free_path(paths);
		return (NULL);
	}
	return (to_test);
}


char	*absolute_path(char *cmd, t_manager *manager)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			access_error(manager, 5, cmd);
			return (NULL);
		}
	}
	else
		return (NULL);
}
