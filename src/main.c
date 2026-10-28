/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:09:28 by norabino          #+#    #+#             */
/*   Updated: 2026/10/28 15:55:50 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"


t_select	*get_sel(void)
{
	static t_select	sel;

	return (&sel);
}

int	init_items(t_select *s, int ac, char **av)
{
	int			i;
	int			idx;

	s->items = malloc(sizeof(t_item) * (ac - 1));
	if (!s->items)
		return (1);
	i = 1;
	idx = 0;
	while (i < ac)
	{
		if (av[i][0] == 0)
		{
			i++;
			continue ;
		}
		s->items[idx].str = ft_strdup(av[i]);
		s->items[idx].selected = 0;
		if (!s->items[idx].str)
		{
			ft_error("error: ft_strdup");
			return (1);
		}
		s->items[idx].len = ft_strlen(av[i]);
		if (s->items[idx].len > s->maxlen)
			s->maxlen = s->items[idx].len;
		i++;
		idx++;
	}
	s->count = idx;
	return (0);
}

int ft_select(t_select *s, int ac, char **av)
{

	if (init_items(s, ac, av))
		quit_select(s, 1);
	if (s->count == 0)
	{
		ft_error("error: no arguments.\n");
		quit_select(s, 1);
	}
	if (init_terminal(s))
		quit_select(s, 1);
	if (print_elems(s))
		quit_select(s, 1);
	if (read_inputs(s))
	{
		ft_error("error: read_inputs");
		quit_select(s, 1);
	}
	if (terminfo_exec("cl", -1, -1))
		quit_select(s, 1);
	if (terminfo_exec("ve", -1, -1))
		quit_select(s, 1);
	
	return (0);
}

int	main(int ac, char **av)
{
	t_select	*s;

	if (ac < 2)
		return (ft_error("Wrong usage.\nTry: ./ft_select choice1 choice2 ..."));
	s = get_sel();
	init_signals(s);
	if (ft_select(s, ac, av))
		quit_select(s, 1);
	if (!s->escaped)	
	{
		if (print_result(s))
		{
			quit_select(s, 1);
			return (1);
		}
	}
	quit_select(s, 0);
}
