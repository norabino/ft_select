/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 17:26:00 by norabino          #+#    #+#             */
/*   Updated: 2026/10/29 17:26:11 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	save_term_settings(t_select *s)
{
	if (tcgetattr(s->fd, &s->orig) == -1)
		ft_error("error: tcgetattr()\n");
}

char	*find_term_path(void)
{
	char	*path;

	if (isatty(0) == 0)
		ft_error("Can't execute ft_select in a pipe.\n");
	path = ttyname(0);
	if (!path)
		ft_error("error: ttyname(0)\n");
	return (path);
}

void	open_term_fd(t_select *s, char *path)
{
	s->fd = open(path, O_RDWR);
	if (s->fd == -1)
		ft_error("error: open()\n");
}

void	load_term_entry(void)
{
	char	*termname;

	termname = getenv("TERM");
	if (!termname)
		ft_error("error: getenv. No environment found.\n");
	if (tgetent(NULL, termname) != 1)
		ft_error("error: tgetent\n");
}

// vi : cacher curseur
// ti : aller sur term alternatif
void	load_raw_mode(t_select *s)
{
	terminfo_exec("vi", -1, -1);
	terminfo_exec("ti", -1, -1);
	s->raw = s->orig;
	s->raw.c_lflag &= ~(ICANON | ECHO);
	s->raw.c_cc[VMIN] = 1;
	s->raw.c_cc[VTIME] = 0;
	tcsetattr(s->fd, TCSANOW, &s->raw);
	s->term_ready = 1;
}
