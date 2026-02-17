/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:57:51 by mmychaly          #+#    #+#             */
/*   Updated: 2024/06/03 13:25:24 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*new_elem;
	void	*new_content;

	start = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst != NULL)
	{
		new_content = f(lst->content);
		new_elem = ft_lstnew(new_content);
		if (new_elem != NULL)
			ft_lstadd_back(&start, new_elem);
		else
		{
			del(new_content);
			ft_lstclear(&start, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (start);
}
