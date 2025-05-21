/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:15:30 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/07 15:24:20 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the length of a NULL-terminated array of strings.
 *
 * This function counts the number of elements in a string array
 * (`char **tab`) that is terminated by a NULL pointer.
 *
 * @param str_array A NULL-terminated array of strings.
 * @return The number of strings in the array. Returns 0 if `str_array` is NULL.
 */
int	ft_strarr_len(char **str_array)
{
	int	i;

	i = 0;
	if (!str_array)
		return (i);
	while (str_array[i])
		i++;
	return (i);
}
