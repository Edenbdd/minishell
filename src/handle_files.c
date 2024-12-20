/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:06:55 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/20 16:58:28 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Check & handles infiles and outfiles access included heredoc creation

#include "minishell.h"
#include "libft.h"

//pcq pour le heredoc on va creer un fichier temporaire
int	check_heredoc(t_manager *manager)
{
	(void)manager; //needed for the error handling

	if (!access("heredoc_tmp", F_OK))
	{
		if (access("heredoc_tmp", R_OK | W_OK))
			return (access_error(manager, 5, "heredoc")); //ok
	}
	return (0);
}

//this needs ot be before in the redir loop !!!
int	check_infile(char *infile, t_manager *manager)
{
	(void)manager;

	if (infile)
	{
		if (access(infile, F_OK) == -1)
			return (access_error(manager, 5, infile)); //ok
		if (access(infile, R_OK) == -1)
			return (access_error(manager, 5, infile)); //ok
	}
	return (0);
}

int	check_outfile(char *outfile, t_manager *manager)
{
	(void)manager;

	if (outfile && !access(outfile, F_OK))
	{
		if (access(outfile, W_OK) == -1)
			return (access_error(manager, 5, outfile));
	}
	return (0);
}

//gere la creation du fichier temporaire heredoc et le met dans previous_fd

int	create_doc(t_manager *manager, int *previous_fd,  t_cmd *current_cmd, t_env *s_env)
{
	*previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*previous_fd == -1)
	{
		// printf("exit possible 1\n");
		return (open_close_error(manager, 1));
	}
	if (create_doc_loop(previous_fd, manager, current_cmd, s_env) == -1)
	{	
		// printf("exit possible 2\n");
		return (-1);
	}
	if (close(*previous_fd) == -1)
	{ 
		// printf("exit possible 3\n");
		return (open_close_error(manager, 1));
	}
	*previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT, 0644);
	if (*previous_fd == -1)
	{
		// printf("exit possible 4\n");
		return (open_close_error(manager, 1));
	}
	return (0);
}
int		create_doc_loop(int *previous_fd, t_manager *manager, t_cmd *current_cmd, t_env *s_env)
{
	char	*current_line;
	char	*tmp;

	tmp = ft_strjoin(current_cmd->lim, "\n");
	if (!tmp)
		return (open_close_error(manager, 6));
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
			// printf("after expand heredoc, current_line is [%s]\n", current_line);
			free(tmp2);
		}
		if (write(*previous_fd, current_line, ft_strlen(current_line)) == -1)
			return (open_close_error(manager, 5));
		free(current_line);
	}
	return (0);
}
//Fonction originale en commentaire
// int	create_doc(t_manager *manager, int *previous_fd, char *lim)
// {
// 	char	*current_line;
// 	char	*tmp;

// 	(void)manager; //sera utiliser pour les sorties d erreur (protection)
// 	*previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (*previous_fd == -1)
// 		return (open_close_error(manager, 1));
// 	tmp = ft_strjoin(lim, "\n"); //PROTEGER LE JOIN
// 	if (!tmp)
// 		return (open_close_error(manager, 6));
// 	while (1)
// 	{
// 		write(1, ">", 1);
// 		current_line = get_next_line(STDIN_FILENO);
// 		if (!current_line
// 			|| !ft_strncmp(current_line, tmp, ft_strlen(current_line)))
// 		{
// 			free(tmp);
// 			free(current_line);
// 			break ;
// 		}
// 		if (write(*previous_fd, current_line, ft_strlen(current_line)) == -1) //ajuster la protection
// 			return (open_close_error(manager, 5));
// 		free(current_line);
// 	}
// 	if (close(*previous_fd) == -1) 
// 		return (open_close_error(manager, 1));
// 	*previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT, 0644);
// 	if (*previous_fd == -1)
// 		return (open_close_error(manager, 1));
// 	return (0);
// }
