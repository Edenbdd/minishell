/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:19 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/09 18:34:13 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//trouver le bon chemin associer avec la cmd

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
	if (!s_env || cmd[0] == '.' || cmd[0] == '/') //gerer les paths absolut/relatif et sans env
		return (absolute_path(cmd, manager));
	paths = ft_split(get_path(s_env), ':');
	if (!paths) 
		return (NULL); //faire une sortie d erreur correcte si fail du split !
	right_path = test_path(paths, cmd, manager);
	free_path(paths);//a ajouter dans free
	if (!right_path)
		return (NULL); //gerer la sortie d erreur si opas de right path trouver
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
		free_path(paths); //pareil a ajouter au free
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

char	*test_path(char **paths, char *cmd, t_manager *manager)
{
	int		i;
	char	*to_test;
	char	*right_path;

	i = 0;
	right_path = NULL;
	while (paths[i])
	{
		to_test = join_path(paths[i], cmd, manager, paths);
		if (to_test == NULL)
			return (NULL);
		if (access(to_test, F_OK) == 0)
		{
			if (access(to_test, X_OK) == 0)
			{
				if (right_path)
					free(right_path);
				right_path = ft_strdup(to_test);
			}
			else
				right_path = NULL;
		}
		free(to_test);
		i++;
	}
	return (right_path);
}

char	*absolute_path(char *cmd, t_manager *manager)
{
	(void)manager;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			//gestion d erreur ici
			return (NULL);
		}
	}
	else
		return (NULL);
}
