/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:04:14 by jgossard          #+#    #+#             */
/*   Updated: 2025/01/29 12:29:20 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Copies n bytes from memory area src to memory area dest.
 * 			The memory areas may overlap.
 *
 * @param dest The destination memory area.
 * @param src The source memory area.
 * @param n The number of bytes to copy.
 * @return A pointer to the destination memory area dest.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	if (dest < src)
		dest = ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			n--;
			((char *)dest)[n] = ((char *)src)[n];
		}
	}
	return (dest);
}
