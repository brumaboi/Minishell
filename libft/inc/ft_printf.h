/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:14:38 by sbruma            #+#    #+#             */
/*   Updated: 2024/05/09 10:47:20 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

int		ft_print_percent_char(va_list args, const char *format);
int		ft_print_idecimal(va_list args);
int		ft_print_hex(va_list args, const char *format);
int		ft_print_pointer(va_list args);
int		ft_print_string(va_list args);
int		ft_print_udecimal(va_list args);
int		ft_printf(const char *fp, ...);

#endif