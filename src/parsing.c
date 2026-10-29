/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 16:53:04 by norabino          #+#    #+#             */
/*   Updated: 2026/10/29 19:00:22 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	identify_input(char *tab, int nb)
{
	if (nb <= 0)
		return (ESCAPE);
	if (nb == 1 && !ft_strncmp(tab, " ", nb))
		return (SPACE);
	else if (nb == 1 && !ft_strncmp(tab, "\n", nb))
		return (ENTER);
	else if (nb == 1 && !ft_strncmp(tab, "\033", nb))
		return (ESCAPE);
	else if (nb == 1 && !ft_strncmp(tab, "\177", nb))
		return (BACKSPACE);
	else if (nb == 3 && !ft_strncmp(tab, "\033[A", nb))
		return (ARROW_UP);
	else if (nb == 3 && !ft_strncmp(tab, "\033[B", nb))
		return (DOWN);
	else if (nb == 3 && !ft_strncmp(tab, "\033[C", nb))
		return (RIGHT);
	else if (nb == 3 && !ft_strncmp(tab, "\033[D", nb))
		return (LEFT);
	else if (nb == 4 && !ft_strncmp(tab, "\033[3~", nb))
		return (DELETE);
	return (-1);
}

int	key_pressed(t_select *s, int input)
{
	if (input == -1)
		return (0);
	if (input == SPACE)
		space(s);
	else if (input == ENTER)
		enter(s);
	else if (input == ESCAPE)
		escape(s);
	else if (input == DELETE || input == BACKSPACE)
		delete(s);
	else if (input == ARROW_UP)
		upkey(s);
	else if (input == DOWN)
		downkey(s);
	else if (input == RIGHT)
		rightkey(s);
	else if (input == LEFT)
		leftkey(s);
	if (input == ENTER || input == ESCAPE)
		return (0);
	return (1);
}
