/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:42:50 by jgossard          #+#    #+#             */
/*   Updated: 2024/12/05 15:41:51 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Concatenates the string src to the end of dst,
 * 			ensuring the result is null-terminated.
 *
 * This function appends the null-terminated string src to the end of dst.
 * It will append at most siz - strlen(dst) - 1 bytes,
 * null-terminating the result.
 *
 * @param dst The destination string.
 * @param src The source string.
 * @param siz The total size of the destination buffer.
 * @return The total length of the string it tried to create.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (siz <= dst_len)
		return (src_len + siz);
	while (src[i] && ((dst_len + i) < (siz - 1)))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}
