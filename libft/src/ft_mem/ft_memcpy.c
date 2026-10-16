/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:05:28 by norabino          #+#    #+#             */
/*   Updated: 2025/01/09 10:34:31 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (src == 0 && n != 0 && dest == 0)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	while (n--)
		d[n] = s[n];
	return (dest);
}
/*
int main ()
{
   printf("Og func = %s\n", memcpy((void*)0, (void*)0, 3));
   printf("My func = %s\n", ft_memcpy((void*)0, (void*)0, 3));

   return(0);
}*/
