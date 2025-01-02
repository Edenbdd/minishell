/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:00:56 by smolines          #+#    #+#             */
/*   Updated: 2025/01/02 18:33:41 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//fonctions pour free les differentes struct

#include "minishell.h"
#include "libft.h"

void	free_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token)
	{
		tmp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = tmp;
	}
	token = NULL;
}

void	free_export(t_export *export)
{
	t_export	*tmp;

	if (!export)
		return ;
	while (export)
	{
		tmp = export->next;
		if (export->field)
			free(export->field);
		if (export->content)
			free(export->content);
		free(export);
		export = tmp;
	}
	export = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->path)
			free(cmd->path);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->lim)
			free(cmd->lim);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->args)
			free_cmd_args(cmd->args);
		free(cmd);
		cmd = tmp;
	}
	cmd = NULL;
}

void	free_manager(t_manager *manager)
{
	if (!manager)
		return;
	if (manager->token_first)
		free_token(manager->token_first); 
	if (manager->cmd_first)
		free_cmd(manager->cmd_first);
	manager = NULL;
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		if (env->field)
			free(env->field);
		if (env->content)
			free(env->content);
		free(env);
		env = tmp;
	}
	env = NULL;
}
