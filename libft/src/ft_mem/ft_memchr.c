/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:32:51 by norabino          #+#    #+#             */
/*   Updated: 2025/01/09 10:34:24 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_p;
	unsigned char	c_p;

	i = 0;
	s_p = (unsigned char *)s;
	c_p = (unsigned char)c;
	while (i < n)
	{
		if (s_p[i] == c_p)
			return (&s_p[i]);
		i++;
	}
	return (NULL);
}
