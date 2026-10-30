/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 17:26:00 by norabino          #+#    #+#             */
/*   Updated: 2026/10/30 14:48:22 by norabino         ###   ########.fr       */
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

void	check_codes(void)
{
	char	*mandatory_codes;
	int		i;
	char	code[3];
	char	*cmdinfo;

	mandatory_codes = "cmclmrusme";
	i = 0;
	while (i < 10)
	{
		code[0] = mandatory_codes[i];
		code[1] = mandatory_codes[i + 1];
		code[2] = 0;
		cmdinfo = tgetstr(code, NULL);
		if (!cmdinfo)
			ft_error("error: mandatory code (cm,cl,mr,us,me) not found.\n");
		i += 2;
	}
}

void	load_term_entry(void)
{
	char	*termname;

	termname = getenv("TERM");
	if (!termname)
		ft_error("error: getenv. No environment found.\n");
	if (tgetent(NULL, termname) != 1)
		ft_error("error: tgetent\n");
	check_codes();
}
