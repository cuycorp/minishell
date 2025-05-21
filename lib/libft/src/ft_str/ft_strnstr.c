/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:31:42 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:36:08 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of the null-terminated string little
 * in the string big, where not more than len characters are searched.
 *
 * This function locates the first occurrence of the null-terminated string
 * little in the string big, where not more than len characters are searched.
 * Characters that appear after a '\0' character are not searched.
 *
 * @param big The string to be searched.
 * @param little The substring to search for.
 * @param len The maximum number of characters to search.
 * @return A pointer to the first occurrence of little in big,
 * or NULL if little is not found.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[i])
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while ((big[i + j]) && (i + j < len) && (big[i + j] == little[j]))
			j++;
		if (!little[j])
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
