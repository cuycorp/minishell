/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:52:26 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:35:53 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Copies up to siz - 1 characters from the NUL-terminated string src
 * 			to dst, NUL-terminating the result.
 *
 * @param dst The destination buffer.
 * @param src The source string.
 * @param siz The size of the destination buffer.
 * @return The total length of the string it tried to create.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	if (siz > 0)
	{
		while ((i < siz - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
