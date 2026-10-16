/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:11:14 by norabino          #+#    #+#             */
/*   Updated: 2026/10/16 13:11:16 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"

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
}	t_select;

t_select	*get_sel(void);
int			ft_error(char *msg);
int			init_items(t_select *s, int argc, char **argv);
void		print_items(t_select *s);
int			free_all(t_select *s);

#endif