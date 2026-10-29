/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:16:41 by norabino          #+#    #+#             */
/*   Updated: 2026/10/29 19:16:09 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	read_inputs(t_select *s, char tab[8], int nb)
{
	int	input;

	input = identify_input(tab, nb);
	if (!key_pressed(s, input))
		return (0);
	return (1);
}

void	check_cursor(t_select *s)
{
	if (s->cursor >= s->count)
		s->cursor = 0;
	if (s->cursor < 0)
		s->cursor = s->count - 1;
}

//nb_cols : nombre de colonnes d'elements ;
//ws.ws_col : largeur en char de la window
int	check_window_size(t_select *s)
{
	int	nb_cols;

	if (ioctl(s->fd, TIOCGWINSZ, &s->ws) == -1)
		ft_error("error: ioctl\n");
	if (s->ws.ws_row == 0)
		return (0);
	nb_cols = (s->count - 1) / s->ws.ws_row + 1;
	if ((s->maxlen + 1) * nb_cols > s->ws.ws_col)
		return (0);
	return (1);
}

void	del_current_elem(t_select *s)
{
	int	i;

	i = s->cursor;
	free(s->items[i].str);
	while (i < s->count - 1)
	{
		s->items[i] = s->items[i + 1];
		i++;
	}
	s->count--;
}
