/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:31:22 by norabino          #+#    #+#             */
/*   Updated: 2026/10/30 12:25:03 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	set_item(t_select *s, char **av, int *i, int *idx)
{
	s->items[*idx].str = ft_strdup(av[*i]);
	if (!s->items[*idx].str)
		ft_error("error: ft_strdup.\n");
	s->items[*idx].selected = 0;
	if ((int)ft_strlen(s->items[*idx].str) > s->maxlen)
		s->maxlen = ft_strlen(s->items[*idx].str);
	(*i)++;
	(*idx)++;
}

void	init_items(t_select *s, int ac, char **av)
{
	int			i;
	int			idx;

	s->items = malloc(sizeof(t_item) * (ac - 1));
	if (!s->items)
		ft_error("error: malloc items.\n");
	i = 1;
	idx = 0;
	while (i < ac)
	{
		if (av[i][0] == 0)
		{
			i++;
			continue ;
		}
		set_item(s, av, &i, &idx);
	}
	s->count = idx;
	if (s->count == 0)
		ft_error("error: no such arguments.\n");
}

void	init_terminal(t_select *s)
{
	char	*path;

	path = find_term_path();
	open_term_fd(s, path);
	save_term_settings(s);
	load_term_entry();
	load_raw_mode(s);
}
