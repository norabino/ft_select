/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 16:52:32 by norabino          #+#    #+#             */
/*   Updated: 2026/10/29 19:36:25 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

// mr : mode inversé
// us : souligner
void	set_format(t_select *s, int i)
{
	if (s->items[i].selected)
		terminfo_exec("mr", -1, -1);
	if (s->cursor == i)
		terminfo_exec("us", -1, -1);
}

// cl : ancien clear
// cm : deplacer curseur
// me : reset formatage
int	print_elems(t_select *s)
{
	int	i;
	int	line;
	int	col;
	int	pos_x;

	terminfo_exec("cl", -1, -1);
	if (!check_window_size(s))
		return (ft_putstr_fd("NOT ENOUGH SIZE.", s->fd), 0);
	i = 0;
	while (i < s->count)
	{
		line = i % s->ws.ws_row;
		col = i / s->ws.ws_row;
		pos_x = col * (s->maxlen + 1);
		terminfo_exec("cm", pos_x, line);
		set_format(s, i);
		ft_putstr_fd(s->items[i].str, s->fd);
		terminfo_exec("me", -1, -1);
		i++;
	}
	return (0);
}

// cl : ancien clear
// te : revenir ecran normal
void	print_result(t_select *s)
{
	int	i;
	int	first;

	terminfo_exec("cl", -1, -1);
	terminfo_exec("te", -1, -1);
	i = 0;
	first = 1;
	while (i < s->count)
	{
		if (s->items[i].selected)
		{
			if (!first)
				ft_putstr_fd(" ", 1);
			first = 0;
			ft_putstr_fd(s->items[i].str, 1);
		}
		i++;
	}
}

int	ft_putchar_select(int c)
{
	t_select	*s;

	s = get_sel();
	ft_putchar_fd(c, s->fd);
	return (0);
}

void	ft_error(char *str)
{
	t_select	*s;

	s = get_sel();
	ft_putstr_fd(str, 2);
	quit_select(s, 1);
}
