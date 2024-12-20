/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:10:09 by smolines          #+#    #+#             */
/*   Updated: 2024/12/20 18:21:54 by smolines         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

// pour gerer $?

#include "minishell.h"
#include "libft.h"

// // stocker un entier errno dans une chaîne de caractères
// char *	errno_to_str(int errno_value, char *err_str)
//  {
//     int	i;

// 	i = 0;
//     if (errno_value == 0) 
// 	{
//         err_str[i] = '0';
// 		i++;
// 	} 
// 	else {
//         while (errno_value > 0) 
// 		{
//             err_str[i] = (errno_value % 10) + '0';
// 		printf("err_str[i] : %c\n", err_str[i]);
// 			i++;
//             errno_value /= 10;
//         }
//     }
//     err_str[i] = '\0';
// 		printf("err_str : %s\n", err_str);
// 	return (err_str);
//  }

// // Inverser la chaîne errno pour obtenir l'ordre correct
// char *errno_inorder(char* err_str, int i)
// {
//     int start = 0;
//     int end = i - 1;
//     while (start < end) 
// 	{
//         char temp = err_str[start];
//         err_str[start] = err_str[end];
//         err_str[end] = temp;
//         start++;
//         end--;
//     }
// 	err_str[start] = '\0';
//     return (err_str);
// }

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
char *expand_errno(t_manager *manager, char *expand_word)
{
	int 	len_errno;

	if ((manager->exit_status < 0) || (manager->exit_status > 128))
		return (NULL);
	// printf("\033[32mmanager->exit_status : %d\033[0m\n", manager->exit_status);
	// printf("\033[32expand word exit_status : %s\033[0m\n", expand_word);
	
	len_errno = errno_len(manager->exit_status);
	// expand_word = (char *)malloc(sizeof(char) * (len_errno + 1));
	// if (!expand_word)
	// 	return (NULL);
	
	expand_word = ft_itoa(manager->exit_status);	
	// expand_word =	errno_to_str(manager->exit_status, expand_word);
	// expand_word = errno_inorder(expand_word, len_errno);

//	printf("\033[32mexpand errno : [%s]\033[0m\n", expand_word);
//	printf("\033[32mtaille errno : [%d]\033[0m\n", len_errno);
	return (expand_word);
}


// int	expand_errno(t_manager *manager, int i)
// {
// 	int		j;
// 	int 	len_errno;

// 	j = 0;

// 	len_errno = errno_len(manager->exit_status);
// 	manager->word = (char *)malloc(sizeof(char) * (len_errno + 1));
// 	if (!manager->word)
// 		return (-1);

// 	j =	errno_to_str(manager->exit_status, manager->word);
// 	manager->word = errno_inorder(manager->word, j);

// 	printf("errno str : [%s]\n", manager->word);
// 	printf("taille errno : [%d]\n", len_errno);
// 	return (i + 1);
// }