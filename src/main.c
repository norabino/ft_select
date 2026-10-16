/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:09:28 by norabino          #+#    #+#             */
/*   Updated: 2026/10/16 13:11:08 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_items(t_select *s)
{
	int	i;

	if (!s || !s->items)
	{
		ft_printf("No items to display\n");
		return ;
	}
	i = 0;
	ft_printf("count=%d cursor=%d maxlen=%d\n", s->count, s->cursor, s->maxlen);
	while (i < s->count)
	{
		ft_printf("[%d] selected=%d len=%d item=[%s]\n", i, s->items[i].selected,
			s->items[i].len, s->items[i].str);
		i++;
	}
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
		s->items[idx].len = ft_strlen(av[i]);
		s->items[idx].selected = 0;
		if (s->items[idx].len > s->maxlen)
			s->maxlen = s->items[idx].len;
		i++;
		idx++;
		s->count++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_select	*s;

	if (ac < 2)
		return (ft_error("usage: ft_select choice1 [choice2 ...]"));
	s = get_sel();
	if (!init_items(s, ac, av))
		return (ft_error("malloc failed"));
	if (s->count == 0)
	{
		free_all(s);
		return (ft_error("usage: ft_select choice1 [choice2 ...]"));
	}
	print_items(s);
	free_all(s);
	return (0);
}
