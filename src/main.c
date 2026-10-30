/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:09:28 by norabino          #+#    #+#             */
/*   Updated: 2026/10/30 15:36:05 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	quit_select(t_select *s, int exitcode, int printing)
{
	if (s->term_ready)
	{
		restore_terminal(s);
		if (printing)
			print_result(s);
		close(s->fd);
	}
	free_all(s);
	exit(exitcode);
}

void	free_all(t_select *s)
{
	int	i;

	i = 0;
	while (i < s->count)
	{
		free(s->items[i].str);
		i++;
	}
	free(s->items);
}

// clear
// ve : réaffiche le curseur
int	main(int ac, char **av)
{
	t_select	*s;

	if (ac < 2)
		ft_error("Wrong usage.\nTry: ./ft_select choice1 choice2 ...\n");
	s = get_sel();
	init_signals();
	init_items(s, ac, av);
	init_terminal(s);
	ft_select(s);
	quit_select(s, 0, !s->escaped);
}
