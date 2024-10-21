/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:29:33 by marvin            #+#    #+#             */
/*   Updated: 2024/10/17 16:29:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_ast *build_ast(t_token *tokens)
{
    t_ast *ast;
    t_token *current;

    current = tokens;
    ast = parse_command(&current); //function to parse input until the next operator
    if (!ast)
        return (NULL); // need to see how to handle this error
    while(current)
    {
        ast = parse_operators(&current, &ast); //function to parse the operator
        if (!ast)
            return (NULL); // need to see how to handle this error
    }
    return (ast);
}

