/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/06 15:09:24 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Everything related to the execution

#include "minishell.h"
#include "libft.h"


//voir comment integrer les heredocs dans le truc sans faire de la merde
//verifier la logique car quelques diff avec le pipex de base !
int	execution(t_manager *manager, t_env *s_env)
{
	t_cmd	*current_cmd;
	int		id;
	int		previous_fd;

	previous_fd = 0; //voir plus tard si je le met a -1 ou si je le laisse a 0 pour que cela corresponde a stdin de base ??
	current_cmd = manager->cmd_first;
	while (current_cmd)
	{
		pipe(current_cmd->pfd); //A PROTEGER
		id = fork(); //A PROTEGER
		if (id == 0)
			child_process(current_cmd, &previous_fd, s_env, manager);
		close(current_cmd->pfd[1]); //A PROTEGER
		if (current_cmd->index >= 1)
			close(previous_fd); //A PROTEGER
		previous_fd = current_cmd->pfd[0];
		current_cmd = current_cmd->next;
	}
	//ici il y a un big free pour tout clean je pense (clean manager en entier)
	return (waiting(id)); //id is gonna be the last child's id
}

//cmd test: echo "hello Pierre et $USER in $HOME !" | cat -e | cat -e > out.txt

void	child_process(t_cmd *cmd, int *previous_fd, t_env *s_env, t_manager *manager)
{
	char	*path;
	char	**env_arr;
	printf("here in a new child process for [%s] with id [%d]\n", cmd->args[0], getpid());
	check_access(cmd->lim, cmd->infile, cmd->outfile, manager);
	// if (cmd->lim) //si c est un heredoc, j exec un truc special heredoc???
	if (cmd->infile || cmd->index != 0) //infile ou pas le premier
	{
		printf("is it weird here ?\n");
		*previous_fd = open(cmd->infile, O_RDONLY); //A PROTEGER
		dup2(*previous_fd, STDIN_FILENO); // A PROTEGER
	}
	if (cmd->outfile || cmd->index != (manager->size_cmd + 1)) //outfile ou pas le dernier
	{
		close(cmd->pfd[1]); //PROTEGER LE CLOSE?
		if (cmd->append == 1)
			cmd->pfd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->pfd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//PROTEGER LES OPEN
		dup2(cmd->pfd[1], STDOUT_FILENO); //A PROTEGER
	}
	path = find_path(cmd->args[0], s_env, manager);
	closing(cmd, previous_fd);
	env_arr = convert_env(s_env);
	execve(path, cmd->args, env_arr); //EXECVE A PROTEGER AUSSI !!!
}

//A check et remodifier pour que waiting nous donne bien les bons codes et msg erreurs
int	waiting(int id_last)
{
	int	status;
	int	retcode;

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