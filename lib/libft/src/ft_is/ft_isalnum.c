/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:34:58 by jgossard          #+#    #+#             */
/*   Updated: 2024/12/05 15:18:47 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is alphanumeric.
 *
 * This function checks if the given character is either a digit (0-9) or an
 * alphabetic character (a-z, A-Z).
 *
 * @param c The character to check.
 * @return 1 if the character is alphanumeric, 0 otherwise.
 */
int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
