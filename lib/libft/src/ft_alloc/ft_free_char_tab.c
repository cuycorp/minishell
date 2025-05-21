/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:53:18 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/12 13:41:26 by jgossard         ###   ########.fr       */
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
 * @param tab Pointer to the array of strings to free
 *
 * @note Sets errno to EINVAL if tab is NULL
 */
void	ft_free_char_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
