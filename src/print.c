/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 16:52:32 by norabino          #+#    #+#             */
/*   Updated: 2026/10/28 17:19:54 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

//nb_cols : nombre de colonnes d'elements ; ws.ws_col : largeur en char de la window
int check_window_size(t_select *s)
{
	int nb_cols;

	if (ioctl(s->fd, TIOCGWINSZ, &s->ws) == -1) 
	{
		ft_error("error: ioctl\n");
        return (1);
    }
	if (s->ws.ws_row == 0)
		return (1);
	nb_cols =  (s->count - 1) / s->ws.ws_row + 1;
	if ( (s->maxlen + 1) * nb_cols > s->ws.ws_col)
		return (1);
	return (0);

}
int	set_format(t_select *s, int i)
{
	if (s->items[i].selected)
		{
			if (terminfo_exec("mr", -1, -1))
				return (1);
		}
		if (s->cursor == i)
		{
			if (terminfo_exec("us", -1, -1))
				return (1);
		}
	return (0);
}

int print_elems(t_select *s)
{
	int i;
	int line;
	int col;
	int pos_x;

	if (terminfo_exec("cl", -1, -1))
		return (1);
	if (check_window_size(s))
	{
		ft_putstr_fd("NOT ENOUGH SIZE.", s->fd);
		return (0);
	}
	i = 0;
	while (i < s->count)
	{
		line = i % s->ws.ws_row;
		col = i / s->ws.ws_row;
		pos_x = col * (s->maxlen + 1);
		if (terminfo_exec("cm", pos_x, line))
			return (1);

		if (set_format(s, i))
			return (1);
		ft_putstr_fd(s->items[i].str, s->fd);
		if (terminfo_exec("me", -1, -1))
			return (1);
		i++;
	}
	return (0);	
}

int	print_result(t_select *s)
{
	int i;
	int first;

	if (terminfo_exec("cl", -1, -1))
		return (1);
	if (terminfo_exec("te", -1, -1))
		return (1);
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
	return (0);
}

int	ft_putchar_select(int c)
{
	t_select *s;

	s = get_sel();
	ft_putchar_fd(c, s->fd);	
	return (0);
}

int	ft_error(char *str)
{
	ft_putstr_fd(str, 2);

	return (1);
}