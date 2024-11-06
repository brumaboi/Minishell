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

// set signal handling to ignore SIGINT
void set_signal_ignore()
{
    struct sigaction sa_ignore;
    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sigaction(SIGINT, &sa_ignore, NULL);
}

// restore default signal handling for SIGINT
void set_signal_default()
{
    struct sigaction sa_default;
    sa_default.sa_handler = SIG_DFL;
    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;
    sigaction(SIGINT, &sa_default, NULL);
}

// restore the custom signal handler for SIGINT
void restore_custom_signal_handler()
{
    struct sigaction sa_custom;
    sa_custom.sa_handler = signal_handler; // Your custom signal handler
    sigemptyset(&sa_custom.sa_mask);
    sa_custom.sa_flags = 0;
    sigaction(SIGINT, &sa_custom, NULL);
}

void init_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);  // Set the action for ctrl + c
    signal(SIGQUIT, SIG_IGN); //ctrl + /
}