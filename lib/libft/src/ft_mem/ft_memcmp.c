/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:50:33 by jgossard          #+#    #+#             */
/*   Updated: 2024/12/05 15:30:14 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares the first n bytes of the memory areas s1 and s2.
 *
 * @param s1 The first memory area to compare.
 * @param s2 The second memory area to compare.
 * @param n The number of bytes to compare.
 * @return	Returns zero if the two memory areas are identical,
 *			otherwise returns the difference between the first differing bytes
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	ptr1 = s1;
	ptr2 = s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
