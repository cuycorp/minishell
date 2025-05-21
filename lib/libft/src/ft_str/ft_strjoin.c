/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:21:58 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:35:45 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates and returns a new string,
 * 			which is the result of the concatenation of `s1` and `s2`.
 *
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return A pointer to the newly allocated string,
 * 			or NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, s1_len);
	ft_memcpy(&dest[s1_len], s2, s2_len);
	dest[s1_len + s2_len] = '\0';
	return (dest);
}
