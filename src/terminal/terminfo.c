/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminfo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:32:28 by norabino          #+#    #+#             */
/*   Updated: 2026/10/30 15:17:53 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	terminfo_exec(char *cmd, int col, int line)
{
	char	*cmdinfo;
	char	*gotostr;

	cmdinfo = tgetstr(cmd, NULL);
	if (!cmdinfo)
		return ;
	if (col != -1 && line != -1)
	{
		gotostr = tgoto(cmdinfo, col, line);
		cmdinfo = NULL;
		cmdinfo = gotostr;
	}
	tputs(cmdinfo, 1, ft_putchar_select);
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

//ve : remettre curseur
//te : sortir term alternatif
void	restore_terminal(t_select *s)
{
	char	*te_info;

	terminfo_exec("ve", -1, -1);
	te_info = tgetstr("te", NULL);
	if (te_info)
		terminfo_exec("te", -1, -1);
	else
		terminfo_exec("cl", -1, -1);
	tcsetattr(s->fd, TCSANOW, &s->orig);
}
