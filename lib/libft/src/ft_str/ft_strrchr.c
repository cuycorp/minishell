/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:31:46 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:36:14 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the last occurrence of c (converted to a char) in the string s
 *
 * This function locates the last occurrence of c (converted to a char) in the
 * string s. The terminating null byte is considered part of the string.
 *
 * @param s The string to be searched.
 * @param c The character to be located.
 * @return A pointer to the last occurrence of c in s, or NULL if c is not found
 */
char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
