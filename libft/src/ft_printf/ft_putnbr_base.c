/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:44:09 by norabino          #+#    #+#             */
/*   Updated: 2025/01/14 09:29:11 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_putnbr_base(long nb, char *base, int *ptr_len)
{
	if (nb < 0)
	{
		nb = -nb;
		*ptr_len += ft_print_c('-');
	}
	if (nb > (long int)ft_strlen(base) - 1)
		ft_putnbr_base(nb / ft_strlen(base), base, ptr_len);
	*ptr_len += ft_print_c(base[nb % (unsigned int)ft_strlen(base)]);
}
