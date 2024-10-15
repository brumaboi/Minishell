/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:24:03 by marvin            #+#    #+#             */
/*   Updated: 2024/10/08 17:24:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//abstract syntax tree

int main(int argc, char **argv, char **env)
{
    t_data data;

    //init_signals
    init_data(&data, env);  //initialize env and exp linked lists
    while(1)
    {
        //prompt + user_input fct
        //parse_input - check - tokenize - parse
        //build_ast !!!
        //execute_ast !!!
        //!!!!free the memory
    }
    //!!!!free the memory
    return (0);
}
