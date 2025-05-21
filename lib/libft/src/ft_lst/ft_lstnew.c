/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:25:36 by jgossard          #+#    #+#             */
/*   Updated: 2024/12/03 18:38:30 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Creates a new linked list node.
 *
 * This function allocates memory for a new linked list node,
 *	initializes its content with the provided value,
 *	and sets the next pointer to `NULL`.
 *
 * @param content The content to initialize the new node with.
 * @return	A pointer to the newly created node,
 * 			or `NULL` if the allocation fails.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*dst;

	dst = (t_list *)malloc(sizeof(t_list));
	if (!dst)
		return (NULL);
	dst->content = content;
	dst->next = NULL;
	return (dst);
}
