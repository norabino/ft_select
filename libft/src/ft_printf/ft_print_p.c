/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:14:15 by norabino          #+#    #+#             */
/*   Updated: 2025/01/09 10:39:47 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_putnbr_ptr(unsigned long nb, char *base, int *ptr_len)
{
	if (nb > (long unsigned int)ft_strlen(base) - 1)
		ft_putnbr_ptr(nb / (long unsigned int)ft_strlen(base), base, ptr_len);
	*ptr_len += ft_print_c(base[nb % (long unsigned int)ft_strlen(base)]);
}

int	ft_print_p(void *nb)
{
	int		len;

	if (nb == 0)
		return (ft_print_s("(nil)"));
	len = 0;
	len += ft_print_s("0x");
	ft_putnbr_ptr((unsigned long)nb, "0123456789abcdef", &len);
	return (len);
}
