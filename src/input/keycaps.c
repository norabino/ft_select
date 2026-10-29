/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycaps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:09:21 by norabino          #+#    #+#             */
/*   Updated: 2026/10/29 19:25:30 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	space(t_select *s) //select unselect elem
{
	if (s->items[s->cursor].selected)
		s->items[s->cursor].selected = 0;
	else
		s->items[s->cursor].selected = 1;
	s->cursor++;
	check_cursor(s);
}

void	enter(t_select *s) //leave and print selected elems
{
	s->escaped = 0;
}

void	escape(t_select *s) //leave and print nothing
{
	s->escaped = 1;
}

void	delete(t_select *s) //delete elem
{
	del_current_elem(s);
	check_cursor(s);
}
