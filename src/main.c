/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:09:28 by norabino          #+#    #+#             */
/*   Updated: 2026/10/29 19:29:36 by norabino         ###   ########.fr       */
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
	init_signals(s);
	init_items(s, ac, av);
	init_terminal(s);
	ft_select(s);
	terminfo_exec("cl", -1, -1);
	terminfo_exec("ve", -1, -1);
	if (!s->escaped)
		print_result(s);
	quit_select(s, 0);
}
