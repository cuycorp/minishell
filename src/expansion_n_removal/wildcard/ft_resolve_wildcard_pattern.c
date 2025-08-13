/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolve_wildcard_pattern.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:10:37 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/13 12:29:30 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			free(*matches);
			*matches = NULL;
			return (false);
		}
		(*matches)[1] = NULL;
	}
	return (true);
}

static bool	ft_wildcard_setup(t_shell *data, const char *pattern)
{
	if (!data || !pattern)
		return (false);
	data->wildcard = ft_create_wildcard_context(pattern);
	if (!data->wildcard)
		return (false);
	return (true);
}

static bool	ft_wildcard_process_entries(t_wildcard_context *context)
{
	if (!context)
		return (false);
	while (context->entry)
	{
		if (!ft_process_entry(context))
			return (false);
		context->entry = readdir(context->directory);
	}
	return (true);
}

static bool	ft_wildcard_finalize(t_wildcard_context *context,
	const char *pattern)
{
	if (!context || !pattern)
		return (false);
	closedir(context->directory);
	context->directory = NULL;
	if (!ft_handle_no_matches(context->match_count, &context->matches, pattern))
		return (false);
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
char	**ft_resolve_wildcard_pattern(const char *pattern, t_shell *data)
{
	t_wildcard_context	*context;
	char				**result;

	if (!pattern || !data)
		return (NULL);
	if (!ft_wildcard_setup(data, pattern))
		return (NULL);
	context = data->wildcard;
	if (!ft_wildcard_process_entries(context))
	{
		ft_free_wildcard_context(context);
		data->wildcard = NULL;
		return (NULL);
	}
	if (!ft_wildcard_finalize(context, pattern))
	{
		ft_free_wildcard_context(context);
		data->wildcard = NULL;
		return (NULL);
	}
	result = context->matches;
	context->matches = NULL;
	return (result);
}
