/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:34:11 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/29 16:16:04 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates and returns a substring from the string `src`.
 *
 * The substring begins at index `start` and is of maximum length `len`.
 *
 * @param src The source string from which to create the substring.
 * @param start The start index of the substring in the source string.
 * @param len The maximum length of the substring.
 * @return A null-terminated pointer to the newly allocated substring,
 * 			or NULL if the allocation fails.
 */
char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	src_len;

	if (!src || len <= 0)
		return (NULL);
	src_len = ft_strlen(src);
	if (src_len <= start)
		len = 0;
	if (src_len - start < len)
		len = src_len - start;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
