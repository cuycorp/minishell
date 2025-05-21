/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:16:42 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:33:58 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Deletes and frees all nodes of a linked list.
 *
 * This function deletes and frees all nodes of the list using the function
 * `del` and `free`. The pointer to the list is set to `NULL`.
 *
 * @param lst The address of the pointer to the first element of the list.
 * @param del The function to delete the content of each node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_node;
	t_list	*next_node;

	if (!lst || !del)
		return ;
	current_node = *lst;
	while (current_node)
	{
		next_node = current_node->next;
		ft_lstdelone(current_node, del);
		current_node = next_node;
	}
	*lst = current_node;
}
