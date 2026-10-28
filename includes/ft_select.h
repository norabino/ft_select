/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:11:14 by norabino          #+#    #+#             */
/*   Updated: 2026/10/28 16:30:39 by norabino         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <signal.h>


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
	int		escaped;
	int		term_ready;
	struct	winsize ws;
	struct	termios	orig;
	struct	termios	raw;
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
	DELETE
};


t_select	*get_sel(void);
int			init_items(t_select *s, int argc, char **argv);

int			identify_input(char *tab, int nb);
int			key_pressed(t_select *s, int input);

int			terminfo_exec(char *cmd, int col, int line);
int			read_inputs(t_select *s);
int			init_terminal(t_select *s);
void		check_cursor(t_select *s);
void		restore_terminal(t_select *s);


void 		space(t_select *s);
void		enter(t_select *s);
void		escape(t_select *s);
int			delete(t_select *s);
void		upkey(t_select *s);
void		downkey(t_select *s);
void		rightkey(t_select *s);
void		leftkey(t_select *s);

int			set_format(t_select *s, int i);
int			ft_error(char *msg);
void		print_items(t_select *s);
int			ft_putchar_select(int c);
int			print_result(t_select *s);
int			print_elems(t_select *s);

int			free_all(t_select *s);
void		del_current_elem(t_select *s);

void		init_signals(t_select *s);

void		quit_select(t_select *s, int exitcode);

#endif