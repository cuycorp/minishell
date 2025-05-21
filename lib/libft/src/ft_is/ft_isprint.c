/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:17:33 by jgossard          #+#    #+#             */
/*   Updated: 2024/12/05 15:21:43 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is printable.
 *
 * This function checks if the given character is a printable character
 * (including space) in the ASCII table (32-126).
 *
 * @param c The character to check.
 * @return 1 if the character is printable, 0 otherwise.
 */
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
