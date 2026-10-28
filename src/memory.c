/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 17:41:35 by norabino          #+#    #+#             */
/*   Updated: 2026/10/28 17:27:25 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	quit_select(t_select *s, int exitcode)
{
	if (s->term_ready)
	{
		restore_terminal(s);
		close(s->fd);
	}
	free_all(s);
	exit(exitcode);
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

void	del_current_elem(t_select *s)
{
	int	i;

	i = s->cursor;
	free(s->items[i].str);
	while (i < s->count - 1)
	{
		s->items[i] = s->items[i+1];
		i++;
	}
	s->count--;
}