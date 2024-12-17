
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/12 10:34:46 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//expans : tools to cut keyword

#include "minishell.h"
#include "libft.h"

/*

char	*cut_expand(char *str, int pos)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[j + i])
	{
		if ((j + i) == pos)
		{
			while (str[i + j] && !ft_is_space(str[i + j]))
				j++;
		}
		if (j >= ft_strlen(str))
			break;
		i++;
	}
	if (j >= i)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (i - j + 1));
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while (str[j])
	{	
		if (j == pos)
		{
			while (str[j] && !ft_is_space(str[j]))
				j++;
		}
		result[i] = str[j];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);	
}
*/

//cut_expand : Calculer la longueur de la chaîne finale

int get_cut_length(char *str, int pos)
{
    int i = 0;
    int j = 0;

    while (str[j + i])
    {
        if ((j + i) == pos)
        {
            while (str[i + j] && !ft_is_space(str[i + j]))
                j++;
        }
        if (j >= ft_strlen(str))
            break;
        i++;
    }
    if (j >= i)
        return (-1); // Retourner une erreur si la coupe est invalide
    return (i - j);
}

//cut_expand : Copie la chaine après suppression

void copy_without_expand(char *str, char *result, int pos)
{
    int i = 0;
    int j = 0;

    while (str[j])
    {
        if (j == pos)
        {
            while (str[j] && !ft_is_space(str[j]))
                j++;
        }
        result[i++] = str[j++];
    }
    result[i] = '\0';
}

//recreer la chaine de caractere sans l'intitule de champ
char *cut_expand(char *str, int pos)
{
    char *result;
    int new_length;
    new_length = get_cut_length(str, pos);
    if (new_length == -1)
        return (NULL);
    result = (char *)malloc(sizeof(char) * (new_length + 1));
    if (!result)
        return (NULL);
    copy_without_expand(str, result, pos);
    return (result);
}
