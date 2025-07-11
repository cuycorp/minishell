/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:42:38 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/09 18:57:03 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory for a structure and initializes it to zero
 *
 * This function allocates memory of the specified size and initializes
 * all bytes to zero using ft_memset. It handles error conditions by
 * setting errno and printing appropriate error messages.
 *
 * @param size The size in bytes to allocate
 * @return void* Pointer to the allocated memory, or NULL if allocation fails
 *               or if size is 0
 *
 * @note Sets errno to EINVAL if size is 0
 * @note The returned memory must be freed by the caller when no longer needed
 */
void	*ft_alloc_struct(size_t size)
{
	void	*data;

	if (!size)
	{
		errno = EINVAL;
		perror("Invalid size: cannot allocate memory with size 0.");
		return (NULL);
	}
	data = malloc(size);
	if (!data)
	{
		perror("malloc failed");
		return (NULL);
	}
	ft_memset(data, 0, size);
	if (!data)
		return (NULL);
	return (data);
}

/*
// Version with calloc
void	*ft_create_and_init_struct(size_t size)
{
	void	*data;

	if (!size)
	{
		errno = EINVAL;
		perror("Invalid size: cannot allocate memory with size 0.");
		return (NULL);
	}
	data = calloc(1, size);
	if (!data)
	{
		perror("calloc failed");
		return (NULL);
	}
	return (data);
}
*/

/*
Suggestions for better function name:

- ft_instantiate_struct – Implies both creation and initialization.

- ft_allocate_and_initialize_struct – Very clear and descriptive.

- ft_initialize_struct – Short, but still conveys the creation and
	initialization of the struct.
*/
