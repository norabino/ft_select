/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 19:10:05 by norabino          #+#    #+#             */
/*   Updated: 2026/10/29 19:10:41 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	init_signals(t_select *s)
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

void	init_sig(t_select *s, int sig, void (*handler)(int))
{
	if (signal(sig, handler) == SIG_ERR)
	{
		ft_error("error: signal\n");
		quit_select(s, 1);
	}
}
