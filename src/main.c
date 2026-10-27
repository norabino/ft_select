/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:09:28 by norabino          #+#    #+#             */
/*   Updated: 2026/10/26 17:32:41 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
	}
	s->count = idx;
	return (0);
}

void print_args(t_select *s)
{
	int i;
	int first;

	i = 0;
	first = 1;
	while (i < s->count)
	{
		if (!first)
			ft_putchar_fd('\n', s->fd);
		first = 0;
		ft_putstr_fd(s->items[i].str, s->fd);
		i++;
	}
}

void print_result(t_select *s)
{
	int i;
	int first;
	char *result;

	result = "";
	i = 0;
	first = 1;
	while (i < s->count)
	{
		if (s->items[i].selected)
		{
			if (!first)
				result = ft_strjoin(result, " ");
			first = 0;
			result = ft_strjoin(result, s->items[i].str);
		}
		i++;
	}
	ft_putstr_fd(result, 1);		
}

int	main(int ac, char **av)
{
	t_select	*s;

	if (ac < 2)
		return (ft_error("Wrong usage.\nTry: ./ft_select choice1 choice2 ..."));
	s = get_sel();
	if (init_items(s, ac, av))
		return (ft_error("error: malloc"));
	if (init_terminal(s))
	{
		free_all(s);
		return (1);
	}
	ft_printf("init done\n");
	print_args(s);
	if (read_inputs(s))
	{
		ft_error("error: read_inputs");
		return (1);
	}
	tcsetattr(s->fd, 0, &s->orig);
	print_result(s);
	free_all(s);
	return (0);
}
