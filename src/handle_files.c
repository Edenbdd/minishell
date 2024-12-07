/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:06:55 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/07 16:40:37 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Check & handles infiles and outfiles access included heredoc creation

#include "minishell.h"
#include "libft.h"

//pcq pour le heredoc on va creer un fichier temporaire
void	check_heredoc(t_manager *manager)
{
	(void)manager; //needed for the error handling

	if (!access("heredoc_tmp", F_OK))
	{
		if (access("heredoc_tmp", R_OK | W_OK))
		{
			printf("sortie d erreur a faire 4\n");
			exit (1);
		}
	}
}
//this needs ot be before in the redir loop !!!
void	check_infile(char *infile, t_manager *manager)
{
	(void)manager;

	if (infile)
	{
		if (access(infile, F_OK) == -1)
		{
			printf("sortie d erreur a faire 2\n");
			exit (1);
		}
		if (access(infile, R_OK) == -1)
		{
			printf("sortie d erreur a faire 3\n");
			exit (1);
		}
	}
}

void	check_outfile(char *outfile, t_manager *manager)
{
	(void)manager;

	if (outfile && !access(outfile, F_OK))
	{
		if (access(outfile, W_OK) == -1)
		{
			printf("sortie d erreur a faire 1\n");
			exit (1);
		}
	}
}
//gere la creation du fichier temporaire heredoc et le met dans previous_fd
void	create_doc(t_manager *manager, int *previous_fd, char *lim)
{
	char	*current_line;
	char	*tmp;

	(void)manager; //sera utiliser pour les sorties d erreur (protection)
	*previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	//OPEN A PROTEGER
	tmp = ft_strjoin(lim, "\n"); //PROTEGER LE JOIN
	while (1)
	{
		write(1, ">", 1);
		current_line = get_next_line(STDIN_FILENO);
		if (!current_line
			|| !ft_strncmp(current_line, tmp, ft_strlen(current_line)))
		{
			free(tmp);
			free(current_line);
			break ;
		}
		write(*previous_fd, current_line, ft_strlen(current_line));
		//PROTEGER LE WRITE ?
		free(current_line);
	}
	close(*previous_fd); //PROTEGER LE CLOSE ?
	*previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT, 0644);
	//PROTEGER OPEN
}