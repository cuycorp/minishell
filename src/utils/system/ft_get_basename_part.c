/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_basename_part.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:04:09 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/13 15:27:22 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns the basename part of a given path (like the Unix basename).
 *
 * This function returns a newly allocated string containing the last component
 * of the input path, ignoring any trailing slashes. If the path consists only
 * of slashes or is empty, it returns an empty string.
 *
 * @param path The input path string.
 * @return A newly allocated string containing the basename.
 *         Caller is responsible for freeing it.
 *         Returns NULL if memory allocation fails.
 *
 * @note If @p path is NULL or an empty string, returns an empty string "".
 *
 * @par Examples:
 * @code
 * ft_get_basename_part("/usr/local/bin")    // returns "bin"
 * ft_get_basename_part("/foo/")              // returns "foo"
 * ft_get_basename_part("foo")                // returns "foo"
 * ft_get_basename_part("////")               // returns ""
 * ft_get_basename_part("")                   // returns ""
 * @endcode
 */
char	*ft_get_basename_part(const char *path)
{
	size_t	path_len;
	size_t	basename_end;
	size_t	basename_start;
	size_t	basename_len;

	if (!path || !*path)
		return (ft_strdup(""));
	path_len = ft_strlen(path);
	basename_end = path_len;
	while (basename_end > 0 && path[basename_end - 1] == SLASH_CHARACTER)
		basename_end--;
	if (basename_end == 0)
		return (ft_strdup(""));
	basename_start = basename_end;
	while (basename_start >0 && path[basename_start - 1] != SLASH_CHARACTER)
		basename_start--;
	basename_len = basename_end - basename_start;
	return (ft_substr(path, basename_start, basename_len));
}
