/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminfo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:32:28 by norabino          #+#    #+#             */
/*   Updated: 2026/10/29 18:34:21 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	terminfo_exec(char *cmd, int col, int line)
{
	char	*cmdinfo;
	char	*gotostr;

	cmdinfo = tgetstr(cmd, NULL);
	if (!cmdinfo)
		ft_error("error: tgetstr\n");
	if (col != -1 && line != -1)
	{
		gotostr = tgoto(cmdinfo, col, line);
		cmdinfo = NULL;
		cmdinfo = gotostr;
	}
	if (tputs(cmdinfo, 1, ft_putchar_select) == -1)
		ft_error("error: tputs\n");
}

//ve : remettre curseur
//te : sortir term alternatif
void	restore_terminal(t_select *s)
{
	terminfo_exec("ve", -1, -1);
	terminfo_exec("te", -1, -1);
	tcsetattr(s->fd, TCSANOW, &s->orig);
}
