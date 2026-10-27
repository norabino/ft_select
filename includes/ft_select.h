/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:11:14 by norabino          #+#    #+#             */
/*   Updated: 2026/10/26 16:47:27 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <termios.h>
# include <termcap.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_item
{
	char	*str;
	int		len;
	int		selected;
}	t_item;

typedef struct s_select
{
	t_item	*items;
	int		count;
	int		cursor;
	int		maxlen;
	int		fd;
	int		term_ready;
	struct termios	orig;
	struct termios	raw;
}	t_select;

enum INPUTS {
	SPACE,
	ENTER,
	ESCAPE,
	BACKSPACE,
	ARROW_UP,
	DOWN,
	RIGHT,
	LEFT,
	SUPPR
};

t_select	*get_sel(void);

int			init_items(t_select *s, int argc, char **argv);
int			init_terminal(t_select *s);

int			read_inputs(t_select *s);

int			ft_error(char *msg);
void		print_items(t_select *s);

int			free_all(t_select *s);

#endif