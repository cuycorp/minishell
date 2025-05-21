/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:44:12 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/09 14:07:49 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks whether a character is a whitespace character.
 *
 * This function returns a non-zero value if the character `c` is a
 * whitespace character. Whitespace characters include:
 * - space (' ')
 * - horizontal tab ('\\t')
 * - newline ('\\n')
 * - vertical tab ('\\v')
 * - form feed ('\\f')
 * - carriage return ('\\r')
 *
 * This mimics the behavior of the standard C library function `isspace()`.
 *
 * @param c The character to check, typically passed
 * 			as an `int` to match `unsigned char` or `EOF`.
 * @return Non-zero if `c` is a whitespace character, 0 otherwise.
 */
int	ft_isspace(int c)
{
	return ((c == ' ') || (c >= '\t' && c <= '\r'));
}
