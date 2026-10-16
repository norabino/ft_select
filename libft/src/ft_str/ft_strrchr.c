/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:08:03 by norabino          #+#    #+#             */
/*   Updated: 2024/11/05 10:08:03 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i] != (char)c && i >= 0)
		i--;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}
/*
int main(void)
{
    char    *str = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
    int    c = '\0';
    printf("Og func : %s\n", strrchr(str, c));
    printf("My func : %s\n", ft_strrchr(str, c));
    return 0;
}*/
