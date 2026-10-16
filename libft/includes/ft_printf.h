/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 08:45:41 by norabino          #+#    #+#             */
/*   Updated: 2025/03/13 09:37:29 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "libft.h"

int				ft_printf(const char *format, ...);
int				ft_size(long long nb, long long divisor);
int				ft_print_c(char c);
int				ft_print_s(char	*str);
int				ft_print_d(int nb);
int				ft_print_u(unsigned int n);
int				ft_print_p(void *nb);
int				ft_print_x(unsigned int nb);
int				ft_print_bx(unsigned int nb);
void			ft_putnbr_base(long nb, char *str, int *ptr_len);

#endif