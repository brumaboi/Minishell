/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:34:16 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 21:34:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_ast create_redirection_node(t_token_type type, char *file)
{

}

t_ast parse_redirection(t_token **current, t_ast *ast)
{
    t_token *token;
    char *file;

    token = *current;
    file = NULL;
    if (token && (token->type == T_GREAT || token->type == T_DGREAT || token->type == T_LESS || token->type == T_DLESS))
    {
        token = token->next;
        if (token && token->type == T_IDENTIFIER)
        {
            file = ft_strdup(token->value);
            if (!file)
                return (NULL); // need to see how to handle this error
            token = token->next;
            return(create_redirection_node(token->type, file));
        }
        else
            return (NULL); // need to see how to handle this error
    }
    return (ast);
}
