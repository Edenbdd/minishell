/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:06:55 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/27 12:40:43 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Check & handles infiles and outfiles access related to heredoc creation

#include "minishell.h"
#include "libft.h"

int	check_heredoc(t_manager *manager)
{
	(void)manager; //see if needed for the error handling ?
	if (!access("heredoc_tmp", F_OK))
	{
		if (access("heredoc_tmp", R_OK | W_OK))
			return (access_error(manager, 5, "heredoc"));
	}
	return (0);
}


//handle heredoc temporary file creation and open in it previous_fd
int	create_doc(t_manager *manager, int *previous_fd,  t_cmd *current_cmd, t_env *s_env)
{
	if (*previous_fd != -1 && close(*previous_fd) == -1)
			return (-1);
	*previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*previous_fd == -1)
		return (system_function_error(manager, 1));
	if (create_doc_loop(previous_fd, manager, current_cmd, s_env) == -1)
		return (-1);
	if (close(*previous_fd) == -1)
		return (system_function_error(manager, 1));
	*previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT, 0644);
	if (*previous_fd == -1)
		return (system_function_error(manager, 1));
	return (0);
}
int		create_doc_loop(int *previous_fd, t_manager *manager, t_cmd *current_cmd, t_env *s_env)
{
	char	*current_line;
	char	*tmp;

	tmp = ft_strjoin(current_cmd->lim, "\n");
	if (!tmp)
		return (system_function_error(manager, 6));
	while (1)
	{
		write(1, ">", 1);
		current_line = get_next_line(STDIN_FILENO);
		if (!current_line
			|| !ft_strncmp(current_line, tmp, ft_strlen(current_line)))
			return (free(tmp), free(current_line), 0);
		if (!current_cmd->heredoc_quotes)
		{
			char *tmp2 = ft_strdup(current_line);
			free(current_line);
			current_line = expand_heredoc(tmp2, s_env);
			free(tmp2);
		}
		if (write(*previous_fd, current_line, ft_strlen(current_line)) == -1)
			return (system_function_error(manager, 5));
		free(current_line);
	}
	return (0);
}
