/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:08:20 by jgossard          #+#    #+#             */
/*   Updated: 2024/12/05 15:52:47 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts an uppercase letter to a lowercase letter.
 *
 * This function converts an uppercase letter to the corresponding lowercase
 * letter. If the character is not an uppercase letter, it is returned unchanged
 *
 * @param c The character to be converted.
 * @return The converted lowercase character, or the original character if
 * it is not an uppercase letter.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
