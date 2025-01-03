/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:06:24 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/02 18:57:09 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Main function handle_builtin_export and the display of the var*/

#include "minishell.h"
#include "libft.h"

int handle_builtin_export(t_manager *manager, t_cmd *cmd)
{
    int i;

    if (cmd && cmd->args && !ft_strcmp(cmd->args[0], "export")
        && !cmd->args[1])
    {
        export_display(manager->export_first);
        return (0);
    }
    i = 1;
    while (cmd && cmd->args && cmd->args[i])
    {
        printf("cmd args is: [%s]\n", cmd->args[i]);
        export_var(cmd->args[i], manager); //see if int 0 or -1
        i++;
    }
    return (0);
}

void    sort_exp(t_export *first_export)
{
    t_export    *current;
    t_export    *next_node;
    char        *tmp_field;
    char        *tmp_content;
    
    current = first_export;
    while (current)
    {
        next_node = first_export;
        while (next_node->next)
        {
            if (ft_strcmp(next_node->field, next_node->next->field) > 0)
            {
                tmp_field = next_node->field;
                tmp_content = next_node->content;
                next_node->field = next_node->next->field;
                next_node->content = next_node->next->content;
                next_node->next->field = tmp_field;
                next_node->next->content = tmp_content;
            }
            next_node = next_node->next;
        }
        current = current->next;
    }
}

void	export_display(t_export *first_export)
{
	t_export	*current_exp;

    sort_exp(first_export);
	current_exp = first_export;
	while (current_exp)
	{
        if (current_exp->content)
		    printf("export %s=\"%s\"\n", current_exp->field, current_exp->content);
		else if (!current_exp->content)
		    printf("export %s\n", current_exp->field);
        current_exp = current_exp->next;
	}
}

