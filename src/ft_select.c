/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:32:28 by norabino          #+#    #+#             */
/*   Updated: 2026/10/29 18:34:21 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select	*get_sel(void)
{
	static t_select	sel;

	return (&sel);
}

int	ft_select(t_select *s)
{
	char	tab[8];
	int		nb;

	print_elems(s);
	while (1)
	{
		ft_bzero(tab, 8);
		nb = read(s->fd, tab, 8);
		if (!read_inputs(s, tab, nb))
			break ;
		if (s->count == 0)
			break ;
		print_elems(s);
	}
	return (0);
}
