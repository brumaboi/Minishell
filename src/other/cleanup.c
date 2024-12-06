/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:09:03 by marvin            #+#    #+#             */
/*   Updated: 2024/12/06 20:09:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void cleanup_readline(void)
{
    clear_history();                // Clear history
    rl_free_line_state();           // Free input line state
    rl_cleanup_after_signal();      // Cleanup after signal
}

void free_free(char *input, char **split_result, t_token *tokens, t_ast *ast)
{
    if (input)
        free(input);
    if (split_result)
        free_split(split_result);
    if (tokens)
        free_tokens(tokens);
    if (ast)
        free_ast(ast);
}
