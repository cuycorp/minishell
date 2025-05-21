/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:16:25 by jgossard          #+#    #+#             */
/*   Updated: 2024/12/01 17:58:40 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Allocates memory for an array of nmemb elements of size bytes each
 * 			and initializes all bytes in the allocated storage to zero.
 *
 *	This function is similar to the standard library function calloc.
 *	It ensures that the multiplication of nmemb and size does not overflow.
 *
 * @param nmemb Number of elements to allocate.
 * @param size Size of each element.
 * @return	A pointer to the allocated memory, or NULL if the allocation fails
 *			or if the multiplication of nmemb and size would overflow.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (nmemb != 0 && (size > (((size_t) - 1) / nmemb)))
		return (NULL);
	total_size = nmemb * size;
	ptr = (void *)malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
