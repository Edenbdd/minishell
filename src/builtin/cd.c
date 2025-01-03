/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:48:19 by smolines          #+#    #+#             */
/*   Updated: 2025/01/03 18:14:34 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//built-in for cd

#include "minishell.h"
#include "libft.h"

/// en cours de travaux/////
//attention avec cd - le OLDPWD doit etre affiche a l'ecran
// autres cd : pas d'affichage\

//recuperer le contenu d'un champ de EN le le passer a chdir
int cd_get_env(t_manager *manager, char *field)
{
	char	*expansion;
		
	expansion = expand_exists(field,`	 manager->env_first);
	if (expansion)
		{
		if (chdir(expansion) != 0)
			return (new_builtin_error(manager, "cd", "not define", field));
		}
	else
		return (builtin_error(manager, 2, "cd"));
	return (0);
}

int	handle_cd(t_manager *manager, t_cmd *cmd)
{

//verif nb arguments
	if (count_cmd_args(cmd) >= 2)
		return (builtin_error(manager, 3, "cd"));

//aller au repertoire home
	if (!(cmd->args[1])) || (ft_strcmp(cmd->args[1], "~"))
		return (cd_get_env(manager, "HOME"));

//aller au repertoire precedant
	if (ft_strcmp(cmd->args[1], "-"))
	{
		// recuperer contenu de OLDPWD et le passer en argument a chdir
		if (cd_get_env(manager, "OLDPWD") != 0)
			return (new_builtin_error(manager, "cd", "OLDPWD not define", NULL));
		
		ft_putstr_fd()
	}

//changer de repertoire
	if (chdir(cmd->args[1]) != 0) 
		return (new_builtin_error(manager, "cd", "no such file or directory", cmd->args[1]));

	update_oldpwd(manager);
	update_pwd(manager);
	return (0);
}

// mettre a jour PWD
//stocker le contenu de PWD pour le passer a OLDPWD
//supprimer le contenu de PWD
//remplacer PWD par le chemin actuel cf fonction pwd


int update_pwd(t_manager *manager, char *pwd)
{
	char	*expansion;

	//recuperer le contenu de pwd	
	expansion = expand_exists(PWD, manager->env_first);
	
	//remplacer OLDPWD par ce contenu
	
	
	return (0);
}


// mettre a jour old PWD
//free OLDPWD
//recuperer le contenu de PWD
//remplacer OLDPWD par le contenu de PWD
int update_oldpwd(t_manager *manager, char *new_path)
{
	
	return (0);
}

char	*update_env(char *to_expand, t_env *s_env)
{
	t_env	*current;
	char *pwd_to_update;
	char *oldpwd_to_update;
	pwd_to_update = expand_exists(PWD, manager->env_first);	
	if (!pwd_to_update)
		return (new_builtin_error(manager, "cd", "PWD not define", NULL));
	oldpwd_to_update = expand_exists(OLDPWD, manager->env_first);
	
////////////////////////////// en cours /////////////////////////
	
// remplacer OLDPWD par PWD

	while (s_env)
	{
		if (!ft_strcmp(s_env->field, "OLDPWD"))
		{
			free (s_env->content);
			s_env->content = ft_strdup(pwd_to_update);
		}
		s_env = s_env->next;
		}
	return (NULL);


//remplacer PWD par nouvelle valeur

	while (s_env)
	{
		if (!ft_strcmp(s_env->field, "PWD"))
		{
			free (s_env->content);
			s_env->content = ft_strdup(cmd->args[1]);
		}
		s_env = s_env->next;
		}
	return (NULL);
}




