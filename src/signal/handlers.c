/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 15:37:21 by norabino          #+#    #+#             */
/*   Updated: 2026/10/30 15:35:25 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	handle_quit(int sig)
{
	t_select	*s;

	(void)sig;
	s = get_sel();
	quit_select(s, 1, 0);
}

void	handle_resize(int sig)
{
	t_select	*s;

	(void)sig;
	s = get_sel();
	if (s->term_ready)
		print_elems(s);
}

void	handle_pause(int sig)
{
	t_select	*s;

	(void)sig;
	s = get_sel();
	if (s->term_ready)
	{
		restore_terminal(s);
		init_sig(SIGTSTP, SIG_DFL);
		if (ioctl(s->fd, TIOCSTI, &s->orig.c_cc[VSUSP]) == -1)
			ft_error("error: ioctl\nIf 'sysctl dev.tty.legacy_tiocsti' "
				"return 0, ft_select can't handle ctrl+z.\n");
	}
}

void	handle_resume(int sig)
{
	t_select	*s;

	(void)sig;
	s = get_sel();
	if (s->term_ready)
	{
		tcsetattr(s->fd, TCSANOW, &s->raw);
		terminfo_exec("vi", -1, -1);
		terminfo_exec("ti", -1, -1);
		init_sig(SIGTSTP, handle_pause);
		print_elems(s);
	}
}
