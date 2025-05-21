/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:48:31 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:35:32 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Locates the first occurrence of c (converted to a char)
 *			in the string pointed to by s.
 *
 * The terminating null character is considered to be part of the string.
 *
 * @param s The string to be scanned.
 * @param c The character to be searched in the string.
 * @return A pointer to the first occurrence of the character c in the string s,
 *         or NULL if the character is not found.
 */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (!s[i])
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}
