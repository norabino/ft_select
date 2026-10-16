/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:09:21 by norabino          #+#    #+#             */
/*   Updated: 2026/10/16 13:10:42 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select	*get_sel(void)
{
	static t_select	sel;

	return (&sel);
}

int	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int	free_all(t_select *s)
{
	int	i;

	i = 0;
	while (i < s->count)
	{
		free(s->items[i].str);
		i++;
	}
	free(s->items);
	return (1);
}
