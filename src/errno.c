/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:10:09 by smolines          #+#    #+#             */
/*   Updated: 2024/12/20 14:48:17 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pour gerer $?

#include "minishell.h"
#include "libft.h"

// stocker un entier errno dans une chaîne de caractères
int	errno_to_str(int errno_value, char* err_str)
 {
    int	i;

	i = 0;
    if (errno_value == 0) 
	{
        err_str[i] = '0';
		i++;
	} 
	else {
        while (errno_value > 0) 

		{
            err_str[i] = (errno_value % 10) + '0';
			i++;
            errno_value /= 10;
        }
    }
    err_str[i] = '\0';
	return (i);
 }

// Inverser la chaîne errno pour obtenir l'ordre correct
char *errno_inorder(char* err_str, int i)
{
    int start = 0;
    int end = i - 1;
    while (start < end) 
	{
        char temp = err_str[start];
        err_str[start] = err_str[end];
        err_str[end] = temp;
        start++;
        end--;
    }
	err_str[start] = '\0';
    return (err_str);
}

int	errno_len(int errnb)
{
	if (errnb >= 100)
		return (3);
	if (errnb < 10)
		return (1);
	return (2);
}

///////////////////////////
//recuperer un token "mot"
int	expand_errno(t_manager *manager)
{
	int		j;
	int 	len_errno;

	j = 0;

	len_errno = errno_len(manager->exit_status);
	manager->word = (char *)malloc(sizeof(char) * (len_errno + 1));
	if (!manager->word)
		return (-1);

	j =	errno_to_str(manager->exit_status, manager->word);
	manager->word = errno_inorder(manager->word, j);

	// printf("errno str : [%s]\n", manager->word);
	// printf("taille errno : [%d]\n", len_errno);
	return (len_errno);
}