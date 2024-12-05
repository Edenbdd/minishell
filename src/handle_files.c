/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:06:55 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/05 14:07:23 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Check infiles and outfiles access included heredoc creation

void	check_access(char *infile, char *outfile, t_err *err)
{
	if (err->heredoc)
		infile = NULL;
	if (infile)
	{
		error_exit(access(infile, F_OK), -1, error_msg(err, "infile "), err);
		error_exit(access(infile, R_OK), -1, error_msg(err, "infile "), err);
	}
	if (!access(outfile, F_OK))
		error_exit(access(outfile, W_OK), -1, error_msg(err, "outfile "), err);
}