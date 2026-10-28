/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 15:37:21 by norabino          #+#    #+#             */
/*   Updated: 2026/10/28 17:32:03 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	init_sig(t_select *s, int sig, void (*handler)(int))
{
	if (signal(sig, handler) == SIG_ERR)
	{
		ft_error("error: signal\n");
		quit_select(s, 1);
	}
}

void handle_quit(int sig)
{
	t_select *s;

	(void)sig;
	s = get_sel();
	quit_select(s, 1);
}

void	handle_resize(int sig)
{
	t_select *s;

	(void)sig;
	s = get_sel();
	if (s->term_ready)
		print_elems(s);
}

void	handle_pause(int sig)
{
	t_select *s;

	(void)sig;
	s = get_sel();
	if (s->term_ready)
	{
		restore_terminal(s);
		init_sig(s, SIGTSTP, SIG_DFL);
		if (ioctl(s->fd, TIOCSTI, &s->orig.c_cc[VSUSP]) == -1)
		{
			ft_error("error: ioctl\nIf 'sysctl dev.tty.legacy_tiocsti' return 0, ft_select can't handle ctrl+z.\n");
	        quit_select(s, 1);
	    }
		if (terminfo_exec("te", -1, -1))
		{
			ft_error("error: handle_resume termcaps\n");
			quit_select(s, 1);
		}
	}
}

void	handle_resume(int sig)
{
	t_select *s;

	(void)sig;
	s = get_sel();
	if (s->term_ready)
	{
		tcsetattr(s->fd, TCSANOW, &s->raw);
		if (terminfo_exec("vi", -1, -1))
		{
			ft_error("error: handle_resume termcaps\n");
			quit_select(s, 1);
		}
		if (terminfo_exec("ti", -1, -1))
		{
			ft_error("error: handle_resume termcaps\n");
			quit_select(s, 1);
		}
		init_sig(s, SIGTSTP, handle_pause);
		print_elems(s);
	}
}


void init_signals(t_select *s)
{
	init_sig(s, SIGINT, handle_quit);
	init_sig(s, SIGQUIT, handle_quit);
	init_sig(s, SIGTERM, handle_quit);
	init_sig(s, SIGHUP, handle_quit);
	init_sig(s, SIGUSR1, handle_quit);
	init_sig(s, SIGUSR2, handle_quit);
	init_sig(s, SIGALRM, handle_quit);
	init_sig(s, SIGPIPE, handle_quit);
	init_sig(s, SIGWINCH, handle_resize);
	init_sig(s, SIGTSTP, handle_pause);
	init_sig(s, SIGCONT, handle_resume);

}

