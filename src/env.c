/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:36 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/03 09:10:32 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Fichier pour gerer la verification de l env et sa copie en liste chainee
// manipulable easly dans la structure s_env qui doit etre lie au manager 
//par la suite

#include "minishell.h"
#include "libft.h"

char		*get_name(char *str)
{
	int		len_name;
	char	*name;
	int		i;

	len_name = 0;
	while(str[len_name] && str[len_name] != '=')
		len_name++;
	name = (char *)malloc(sizeof(char) * len_name + 1);
	if (!name)
		return(NULL);
	i = 0;
	while(i < len_name)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);	
}
char	*get_content(char *str)
{
	int		len_content;
	char	*content;
	int		i;

	len_content = 0;
	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	i++;
	while(str[i + len_content])
		len_content++;
	content = (char *)malloc(sizeof(char) * len_content + 1);
	if (!content)
		return(NULL);
	len_content = 0;
	while(str[i + len_content])
	{
		content[len_content] = str[i + len_content];
		len_content++;
	}
	content[len_content] = '\0';
	return (content);
}
t_env	*handle_env(char **env)
{
	int	i;
	t_env	*first_env;
	
	i = 0;
	if (!env)
	{
		printf("why did you do env -i ?\n");
		return (NULL);
	}
	while (env[i])
	{
		if (i == 0)
			first_env = env_new(env[i]);
		else
			env_add_back(first_env, env[i]);
		i++;
	}
	return (first_env);
}