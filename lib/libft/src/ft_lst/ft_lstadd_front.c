/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:34:58 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:33:49 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds the element `new` at the beginning of the list.
 *
 * This function updates the head of the list to point to the new element,
 * and sets the `next` pointer of the new element to the previous head of
 * the list.
 *
 * @param lst A pointer to the pointer to the first element of the list.
 * @param new The new element to add at the beginning of the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*current_head;

	if (!lst && !new)
		return ;
	current_head = *lst;
	new->next = current_head;
	*lst = new;
}
