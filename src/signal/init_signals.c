/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 19:10:05 by norabino          #+#    #+#             */
/*   Updated: 2026/10/30 15:36:33 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	init_signals(void)
{
	init_sig(SIGINT, handle_quit);
	init_sig(SIGQUIT, handle_quit);
	init_sig(SIGTERM, handle_quit);
	init_sig(SIGHUP, handle_quit);
	init_sig(SIGUSR1, handle_quit);
	init_sig(SIGUSR2, handle_quit);
	init_sig(SIGALRM, handle_quit);
	init_sig(SIGPIPE, handle_quit);
	init_sig(SIGABRT, handle_quit);
	init_sig(SIGSEGV, handle_quit);
	init_sig(SIGBUS, handle_quit);
	init_sig(SIGFPE, handle_quit);
	init_sig(SIGWINCH, handle_resize);
	init_sig(SIGTSTP, handle_pause);
	init_sig(SIGCONT, handle_resume);
}

void	init_sig(int sig, void (*handler)(int))
{
	if (signal(sig, handler) == SIG_ERR)
		ft_error("error: signal\n");
}
