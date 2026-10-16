/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:17:36 by norabino          #+#    #+#             */
/*   Updated: 2025/01/09 10:39:58 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_print_x(unsigned int nb)
{
	int	len;

	len = 0;
	ft_putnbr_base(nb, "0123456789abcdef", &len);
	return (len);
}
