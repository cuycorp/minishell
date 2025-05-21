/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:06:35 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:36:20 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Allocates and returns a copy of `src` with the characters specified
 *			in `set` removed from the beginning and the end.
 *
 * @param src The source string to be trimmed.
 * @param set The set of characters to be trimmed from the source string.
 * @return	A pointer to the newly allocated trimmed string, or NULL if the
 *			allocation fails.
 */
char	*ft_strtrim(char const *src, char const *set)
{
	char	*dest;
	int		start;
	int		end;
	int		trim_length;

	if (!src || !set)
		return (NULL);
	start = 0;
	while (src[start] && ft_strchr(set, src[start]))
		start++;
	end = ft_strlen(src);
	while (end > start && ft_strchr(set, src[end - 1]))
		end--;
	trim_length = end - start;
	dest = (char *)malloc((trim_length + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, &src[start], trim_length);
	dest[trim_length] = '\0';
	return (dest);
}
