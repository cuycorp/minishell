/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:16:49 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:34:23 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Iterates over each element of the list `lst` and applies the
 * 			function `f` to the content of each node, creating a new list
 * 			resulting from the successive applications of `f`.
 *
 * This function allocates memory for a new list. If the allocation fails,
 * the function uses `del` to delete the content of any nodes that were
 * already created.
 *
 * @param lst The pointer to the first element of the list.
 * @param f The function to apply to the content of each node.
 * @param del The function to delete the content of a node if allocation fails.
 * @return The new list, or NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	result_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew((*f)(lst->content));
		if (!new_node)
		{
			ft_lstclear(&result_list, del);
			return (NULL);
		}
		ft_lstadd_back(&result_list, new_node);
		lst = lst->next;
	}
	return (result_list);
}
