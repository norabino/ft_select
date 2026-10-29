/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 17:28:41 by norabino          #+#    #+#             */
/*   Updated: 2026/10/28 15:33:30 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	upkey(t_select *s)
{
	s->cursor--;
	check_cursor(s);
}

void	downkey(t_select *s)
{
	s->cursor++;
	check_cursor(s);
}

void	rightkey(t_select *s)
{
	s->cursor += s->ws.ws_row;
	check_cursor(s);
}

void	leftkey(t_select *s)
{
	s->cursor -= s->ws.ws_row;
	check_cursor(s);
}
