/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:02:24 by norabino          #+#    #+#             */
/*   Updated: 2025/01/09 10:32:44 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	temp = new;
	while (lst && lst->next)
	{
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		temp->next = ft_lstnew(f(lst->next->content));
		temp = temp->next;
		lst = lst->next;
	}
	return (new);
}
