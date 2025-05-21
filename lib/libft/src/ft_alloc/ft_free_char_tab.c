/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:53:18 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/22 09:48:19 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees a NULL-terminated array of strings and the array itself
 *
 * This function iterates through a NULL-terminated array of strings,
 * freeing each string and finally freeing the array. It sets the input
 * pointer to NULL after freeing.
 *
 * @param arr Pointer to the array of strings to free
 *
 * @note Sets errno to EINVAL if arr is NULL
 */
void	ft_free_char_tab(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
