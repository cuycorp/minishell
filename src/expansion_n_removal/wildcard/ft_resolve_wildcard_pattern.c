/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolve_wildcard_pattern.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:10:37 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/08 17:46:16 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_process_entry(const char *filename, const char *pattern,
		char ***matches, int *match_count)
{
	if (!filename || !pattern || !matches || !match_count)
		return (false);
	if (filename[0] != DOT_CHARACTER || pattern[0] == DOT_CHARACTER)
	{
		if (ft_check_wildcard_pattern(pattern, filename))
		{
			if (!ft_append_to_string_array(matches, match_count, filename))
				return (false);
		}
	}
	return (true);
}

static bool	ft_handle_no_matches(
	int match_count, char ***matches, const char *pattern)
{
	if (!matches || !pattern)
		return (false);
	if (match_count == 0)
	{
		*matches = malloc(sizeof(char *) * 2);
		if (!*matches)
			return (false);
		(*matches)[0] = ft_strdup(pattern);
		if (!(*matches)[0])
			return (free(matches), false);
		(*matches)[1] = NULL;
	}
	return (true);
}

static bool	ft_setup_wildcard_search(
	DIR **directory, char ***matches, int *match_count, struct dirent **entry)
{
	if (!directory || !matches || !match_count || !entry)
		return (false);
	*directory = opendir(CURRENT_DIRECTORY);
	if (!*directory)
		return (false);
	*matches = NULL;
	*match_count = 0;
	*entry = readdir(*directory);
	return (true);
}

/**
 * @brief Resolves a wildcard pattern to matching filenames in the current
 * directory.
 *
 * This function scans the current directory and collects all filenames that
 * match the given wildcard pattern (supports '*' as the wildcard character).
 * The results are returned as a newly allocated NULL-terminated array of
 * strings.
 *
 * If the pattern does not match any files, the original pattern is returned as
 * the sole element in the array.
 *
 * Hidden files (starting with '.') are only considered if the pattern also
 * starts with '.'.
 *
 * Example:
 * @code
 * // Assuming files: main.c, utils.c, Makefile
 * char **matches = ft_resolve_wildcard_pattern("*.c");
 * // matches → {"main.c", "utils.c", NULL}
 * @endcode
 *
 * @param pattern The wildcard pattern to resolve (e.g., "*.c", "file*").
 *
 * @return A newly allocated NULL-terminated array of matching filenames.
 *         If no matches are found, returns an array with one element containing
 *         a copy of the original pattern.
 *         Returns NULL on allocation error or if pattern is NULL.
 *
 * @see ft_check_wildcard_pattern
 * @see ft_append_to_string_array
 * @see ft_free_char_tab
 */
char	**ft_resolve_wildcard_pattern(const char *pattern)
{
	DIR				*directory;
	struct dirent	*entry;
	char			**matches;
	int				match_count;

	if (!pattern)
		return (NULL);
	if (!ft_setup_wildcard_search(&directory, &matches, &match_count, &entry))
		return (NULL);
	while (entry)
	{
		if (!ft_process_entry(entry->d_name, pattern, &matches, &match_count))
		{
			ft_free_char_tab(matches);
			closedir(directory);
			return (NULL);
		}
		entry = readdir(directory);
	}
	closedir(directory);
	if (!ft_handle_no_matches(match_count, &matches, pattern))
		return (ft_free_char_tab(matches), NULL);
	return (matches);
}
