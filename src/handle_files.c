/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:06:55 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/06 12:04:54 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Check infiles and outfiles access included heredoc creation

#include "minishell.h"

//pcq pour le heredoc on va creer un fichier temporaire
static void	check_heredoc(t_manager *manager)
{
	(void)manager;

	if (!access("heredoc_tmp", F_OK))
	{
		if (access("heredoc_tmp", R_OK | W_OK))
		{
			printf("sortie d erreur a faire 4\n");
			exit (1);
		}
	}
}

void	check_access(char *lim, char *infile, char *outfile, t_manager *manager)
{
	if (lim)
	{
		check_heredoc(manager);
	}
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
	if (outfile && !access(outfile, F_OK))
	{
		if (access(outfile, W_OK) == -1)
		{
			printf("sortie d erreur a faire 1\n");
			exit (1);
		}
	}
}