/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:47:38 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 21:47:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void signal_handler(int signal)
{
    if(signal == SIGINT)
    {
        printf("\n");  //print new line to reset prompt
        rl_on_new_line(); //move to new line
        rl_replace_line("", 0); //replace the current line with nothing
        rl_redisplay(); //redisplay the prompt
    }
}

//NEEDS WORK!!!!
void init_signals(void)
{
    signal(SIGINT, signal_handler); //ctrl + c
    signal(SIGQUIT, SIG_IGN); //ctrl + /
}