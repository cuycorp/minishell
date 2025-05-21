/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:03:52 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:34:50 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Locates the first occurrence of c (converted to an unsigned char)
 *			in the first n bytes of the memory area pointed to by s.
 *
 * @param s The pointer to the memory area to be scanned.
 * @param c The character to be located.
 * @param n The number of bytes to be analyzed.
 * @return A pointer to the matching byte or NULL if the character does not
 * occur in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return (&p[i]);
		i++;
	}
	return (NULL);
}
