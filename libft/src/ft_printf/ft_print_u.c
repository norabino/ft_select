/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:10:07 by norabino          #+#    #+#             */
/*   Updated: 2025/01/09 10:39:54 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_print_u(unsigned int nb)
{
	char			z;
	int				len;

	len = ft_size(nb, 10);
	z = '0';
	if (nb > 9)
		ft_print_u(nb / 10);
	z = z + nb % 10;
	ft_print_c(z);
	return (len);
}
