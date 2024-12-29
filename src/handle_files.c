/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:16:47 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/29 14:38:16 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*get_cut_path(char *path)
{
	char	*result;
	int		i;
	int		count;

	i = ft_strlen(path) - 1;
	// printf("path is [%s]\n with len %d\n", path, i);
	while (path[i] && path[i] != '/')
		i--;
	i--;
	count = 0;
	while (count <= i)
		count++;
	// printf("count is %d\n", count);
	result = (char *)malloc(sizeof(char) * count + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		result[i] = path[i];
		i++;
	}
	result[i] = '\0';
	// printf("at the end of get cut path esult is [%s]\n", result);
	return (result);
}

int	handle_redir_path(t_manager *manager, char *path, t_cmd *cmd)
{
	(void)cmd; // lets see if its ok without it
	char	cwd[1024]; //idk why so much ?
	char	*cut_path;

	getcwd(cwd, sizeof(cwd));
	// printf("ici is: [%s]\n", cwd);
	cut_path = get_cut_path(path);
	if (access(cut_path, F_OK) == -1)
		return (access_error(manager, 6, path));
    return (0);
}
int	check_infile(char *infile, t_manager *manager)
{
	if (infile)
	{
		if (access(infile, F_OK) == -1)
			return (access_error(manager, 6, infile)); //pb gestion d erreur ici !
		if (access(infile, R_OK) == -1)
			return (access_error(manager, 5, infile));
	}
	return (0);
}

int	check_outfile(char *outfile, t_manager *manager, t_cmd *cmd)
{
	int	is_path;
	
	verif_operator(manager, outfile, 0, &is_path);
	if (outfile && !access(outfile, F_OK) //exist mais pemission denied
		&& access(outfile, W_OK) == -1)
			return (access_error(manager, 5, outfile));
	if (outfile && access(outfile, F_OK ) && is_path == DIREC) //doesnt exist et path
	{
		if (handle_redir_path(manager, outfile, cmd) == -1)
			return (-1);
	}
	if (cmd->append == 1 && cmd->outfile)
	{
        cmd->pfd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (cmd->outfile)
	{
		ft_putstr_fd("opening outfile: ", 2);
		ft_putstr_fd(cmd->outfile , 2);
    	ft_putstr_fd("\n" , 2);
		cmd->pfd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	return (0);
}