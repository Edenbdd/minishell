
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

//expans : tools to replace keyword by its content

#include "minishell.h"
#include "libft.h"


/*
char	*replace_expand(char *str, int pos, char *expansion)
{
	char	*result;
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	j = 0;
	while (str[j + i])
	{	
		if ((j + i) == pos)
		{
			while (str[i + j] && !ft_is_space(str[i + j]))
				j++;
		}
		i++;
	}
	result = (char *)malloc(sizeof(char) * (i + ft_strlen(expansion) + 1));
	if (!result)
		return (NULL);
	j = 0;
	k = 0;
	l = 0;
	while (str[j])
	{	
		if (j == pos)
		{
			while (str[j] && !ft_is_space(str[j]))
			{
				j++;
			}
			while (expansion[k])
			{
				result[l] = expansion[k];
				k++;
				l++;
			}
		}
		result[l] = str[j];
		l++;
		j++;
	}
	result[l] = '\0';
	return (result);	
}
*/

//replace expand : Fonction pour calculer la longueur de la chaîne résultante

int replexpand_length(char *str, int pos, char *expansion)
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
        i++;
    }
    return (i + ft_strlen(expansion));
}

//replace expand : copie l'expansion et le reste de la chaîne dans le résultat

void replexpand_copy(char *str, char *result, int pos, char *expansion)
{
    int j = 0;
    int k = 0;
    int l = 0;

    while (str[j])
    {
        if (j == pos)
        {
            while (str[j] && !ft_is_space(str[j]))
                j++;
            while (expansion[k])
                result[l++] = expansion[k++];
        }
        result[l++] = str[j++];
    }
    result[l] = '\0';
}


char *replace_expand(char *str, int pos, char *expansion)
{
    char *result;
    int new_length;

    // Calculer la nouvelle longueur
    new_length = replexpand_length(str, pos, expansion);

    // Allouer la mémoire
    result = (char *)malloc(sizeof(char) * (new_length + 1));
    if (!result)
        return (NULL);

    // Copier la chaîne avec l'expansion
    replexpand_copy(str, result, pos, expansion);

    return (result);
}
