/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:07:46 by norabino          #+#    #+#             */
/*   Updated: 2024/11/05 10:07:46 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (big[0] == '\0' || len == 0)
		return (NULL);
	while (big[i] && j < ft_strlen(little))
	{
		j = 0;
		while (big[i + j] == little[j] && i < len
			&& i + j < len)
		{
			j++;
			if (j == ft_strlen(little))
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
/*
int main()
{
    char    *big = "";
    char    *little = "oh no not the empty string !";
    size_t  len = ft_strlen(little);

    printf("My func : %s", ft_strnstr(big, little, len));
    return (0);
}*/
