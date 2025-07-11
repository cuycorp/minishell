/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:48:18 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/09 18:47:19 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates sufficient memory for a copy of the string s1,
 * 			does the copy, and returns a pointer to it.
 *
 * The pointer may subsequently be used as an argument to the function free(3).
 *
 * @param src The string to duplicate.
 * @return A pointer to the duplicated string
 * 			or NULL if insufficient memory was available.
 */
char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	str_len;

	if (!src)
		return (NULL);
	str_len = ft_strlen(src);
	dest = (char *)malloc((str_len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, src, str_len);
	if (!dest)
		return (NULL);
	dest[str_len] = '\0';
	return (dest);
}
