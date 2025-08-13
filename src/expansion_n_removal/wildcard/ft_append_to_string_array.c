/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_to_string_array.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:11:52 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/13 12:30:26 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Copies pointers from one string array to another.
 *
 * This function copies the first @p length elements from the source string
 * array @p src into the destination array @p dest. It performs a shallow copy
 * of the pointers, not duplicating the strings themselves.
 *
 * @param dest Destination array where string pointers will be copied.
 * @param src Source array from which to copy string pointers.
 * @param length Number of elements to copy.
 *
 * @note Both @p dest and @p src must be allocated and large enough to hold
 *            @p length elements. This function does not allocate memory
 *            or add a NULL terminator.
 */
static void	ft_copy_string_array_content(char **dest, char **src,
	unsigned int length)
{
	unsigned int	i;

	if (!dest || !src || length < 1)
		return ;
	i = 0;
	while (i < length)
	{
		dest[i] = src[i];
		i++;
	}
}

/**
 * @brief Appends a string to a dynamically resizable NULL-terminated string
 * array.
 *
 * This function allocates a new array with space for one additional string
 * and a NULL terminator, copies the existing strings into it, adds a duplicate
 * of the new string (`str`), and updates the array pointer and its length.
 *
 * Memory is managed internally: the old array is freed, and the caller receives
 * a pointer to the new one via `array`.
 *
 * Example usage:
 * @code
 * char **args = NULL;
 * int arg_count = 0;
 * ft_append_to_string_array(&args, &arg_count, "hello");
 * ft_append_to_string_array(&args, &arg_count, "world");
 * // args now contains {"hello", "world", NULL}
 * @endcode
 *
 * @param array  A pointer to the NULL-terminated string array (char ***).
 *               Will be reallocated and updated.
 * @param length A pointer to the current number of strings in the array.
 *               Will be incremented on success.
 * @param str    The string to append. It will be duplicated internally.
 *
 * @return true if the string was successfully appended, false on memory
 *         allocation failure or if any input pointer is NULL.
 *
 * @see ft_strdup
 */
bool	ft_append_to_string_array(char ***array, unsigned int *length,
	const char *str)
{
	char	**resized_array;

	if (!array || !str || !length)
		return (false);
	resized_array = malloc(sizeof(char *) * (*length + 2));
	if (!resized_array)
		return (false);
	if (*array)
		ft_copy_string_array_content(resized_array, *array, *length);
	resized_array[*length] = ft_strdup(str);
	if (!resized_array[*length])
		return (free(resized_array), false);
	(*length)++;
	resized_array[*length] = NULL;
	if (*array)
		free(*array);
	*array = resized_array;
	return (true);
}
