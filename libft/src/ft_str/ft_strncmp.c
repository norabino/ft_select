/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:07:02 by norabino          #+#    #+#             */
/*   Updated: 2024/11/05 10:07:02 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (((unsigned char)s1[i] && (unsigned char)s2[i])
		&& ((unsigned char)s1[i] == (unsigned char)s2[i])
		&& (i < n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int main()
{
    char *str1 = "\x12\xff\x65\x12\xbd\xde\xad";
    char *str2 = "\x12\x02";
	int	i = 0;

	while (str1[i])
	{
		printf("%c\n", str1[i]);
		i++;
	}
	printf("Og func :%d\n", strncmp(str1, str2, 2));
    printf("My func :%d", ft_strncmp(str1, str2, 2));
    return 0;
}
*/
