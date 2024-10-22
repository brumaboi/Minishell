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

//NEEDS WORK!!!!
void init_signals(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
}