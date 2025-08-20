/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_directory_part.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:37:59 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/13 15:29:24 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_get_path_end_without_trailing_slashes(const char *path,
		size_t len)
{
	if (!path)
		return (0);
	while (len > 0 && path[len - 1] == '/')
		len--;
	return (len);
}

static bool	ft_is_only_slashes(const char *path, size_t end)
{
	size_t	i;

	if (!path)
		return (false);
	i = 0;
	while (i < end)
	{
		if (path[i] != SLASH_CHARACTER)
			return (false);
		i++;
	}
	return (true);
}

static size_t	ft_find_last_slash_index_before_basename(const char *path,
		size_t end)
{
	size_t	i;

	if (!path)
		return (0);
	i = end;
	while (i > 0 && path[i - 1] != '/')
		i--;
	return (i);
}

/**
 * @brief Returns the directory part of a given path, similar to dirname().
 *
 * This function returns a newly allocated string containing the directory
 * portion of the input path. It handles trailing slashes correctly, returning
 * "/" if the path consists entirely of slashes, and "." if there is no slash
 * in the path (i.e., the input is just a filename).
 *
 * Trailing slashes are ignored when determining the directory part.
 *
 * @param path The input path string.
 * @return A newly allocated string with the directory part. Caller is
 * responsible for freeing it. Returns NULL on memory allocation failure.
 *
 * @note If @p path is NULL or an empty string, returns a copy of ".".
 *
 * @par Examples:
 * @code
 * ft_get_directory_part("/usr/local/bin")  // returns "/usr/local"
 * ft_get_directory_part("foo")             // returns "."
 * ft_get_directory_part("/foo/")           // returns "/"
 * ft_get_directory_part("////")            // returns "/"
 * ft_get_directory_part("//usr//local/bin///") // returns "//usr//local"
 * @endcode
 */
char	*ft_get_dir_part(const char *path)
{
	char	*directory_value;
	size_t	path_len;
	size_t	trimmed_length;
	size_t	last_slash_index;

	if (!path || !*path)
		return (ft_strdup(CURRENT_DIRECTORY));
	path_len = ft_strlen(path);
	trimmed_length = ft_get_path_end_without_trailing_slashes(path, path_len);
	if (trimmed_length == 0 || ft_is_only_slashes(path, trimmed_length))
		return (ft_strdup(SLASH_STRING));
	last_slash_index = ft_find_last_slash_index_before_basename(path,
			trimmed_length);
	if (last_slash_index == 0)
		return (ft_strdup(CURRENT_DIRECTORY));
	directory_value = malloc(sizeof(char) * (last_slash_index + 1));
	if (!directory_value)
		return (NULL);
	ft_memcpy(directory_value, path, last_slash_index);
	directory_value[last_slash_index] = '\0';
	return (directory_value);
}
