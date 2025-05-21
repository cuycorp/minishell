/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:08:06 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/07 21:36:22 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees a 2D array of integers of specified size
 *
 * This function iterates through a 2D array of integers with the given size,
 * freeing each row and finally freeing the array itself. It sets the input
 * pointer to NULL after freeing.
 *
 * @param tab Pointer to the 2D array of integers to free
 * @param size Number of rows in the array
 *
 * @note Sets errno to EINVAL if tab is NULL or if size is less than 1
 * @note The function will only free non-NULL row pointers
 */
void	ft_free_int_tab(int **tab, size_t size)
{
	size_t	i;

	if (!tab)
	{
		errno = EINVAL;
		perror("Invalid argument: NULL pointer passed");
		return ;
	}
	if (size < 1)
	{
		errno = EINVAL;
		perror("Invalid argument: size must be greater than 0");
		return ;
	}
	i = 0;
	while (i < size)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}
