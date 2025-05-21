/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:04:37 by jgossard          #+#    #+#             */
/*   Updated: 2024/12/05 15:53:24 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a lowercase letter to an uppercase letter.
 *
 * This function converts a lowercase letter to the corresponding uppercase
 * letter.If the character is not a lowercase letter, it is returned unchanged.
 *
 * @param c The character to be converted.
 * @return The converted uppercase character, or the original character if
 * it is not a lowercase letter.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
