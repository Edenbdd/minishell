/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:00:56 by smolines          #+#    #+#             */
/*   Updated: 2024/12/11 15:43:07 by aubertra         ###   ########.fr       */
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
void	free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

int	closing(t_cmd *cmd, int *previous_fd, t_manager *manager)
{
	if (cmd->pfd[1] != -1)
	{
		if (close(cmd->pfd[1]) == -1)
			return (open_close_error(manager, 1));
	}
	if (cmd->pfd[0] != -1)
	{
		if (close(cmd->pfd[0]) == -1)
			return (open_close_error(manager, 1));
	}
	if (*previous_fd != -1)
	{
		if (close(*previous_fd) == -1)
			return (open_close_error(manager, 1));
	}
	return (0);
}

void	unlink_heredoc(t_manager *manager)
{
	(void)manager;
	if (!access("heredoc_tmp", F_OK))
	{
		if (unlink("heredoc_tmp") == -1)
			printf("we need an error handling here\n");
	}
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

void	free_cmd_args(char **args)
{
	int	i;
	
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
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
	if (manager->export_first)
		free_export(manager->export_first);
}
