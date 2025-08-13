/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_wildcard_pattern.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:46:24 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/13 12:38:36 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_match_exact_char(const char *pattern, const char *str,
		int *pattern_index, int *str_index)
{
	if (!pattern || !pattern_index || !str_index || !str)
		return (false);
	if (pattern[*pattern_index] == str[*str_index])
	{
		(*pattern_index)++;
		(*str_index)++;
		return (true);
	}
	return (false);
}

static void	ft_handle_wildcard(int *pattern_index, int *str_index,
		int *last_wildcard_index, int *resume_match_idx)
{
	*last_wildcard_index = *pattern_index;
	*resume_match_idx = *str_index;
	(*pattern_index)++;
}

/**
 * @brief Attempts to backtrack to the last encountered wildcard in the pattern.
 *
 * This function is used when a character mismatch occurs during wildcard
 * pattern matching. If a previous '*' wildcard was found, the function allows
 * retrying the match by advancing the string pointer (one character further)
 * while resetting the pattern index to just after the wildcard.
 *
 * @param pattern_index Pointer to the current index in the pattern string
 * @param str_index Pointer to the current index in the input string
 * @param last_wildcard_index The index of the last seen wildcard in the pattern
 * @param resume_match_idx Pointer to the index from which matching should
 * resume in the input string.
 *
 * @retval true if backtracking was possible (a previous wildcard exists),
 * @retval false if no wildcard was found before the mismatch (match failed).
 */
static bool	ft_backtrack_to_wildcard(int *pattern_index, int *str_index,
		int last_wildcard_index, int *resume_match_idx)
{
	if (!pattern_index || !str_index || !resume_match_idx)
		return (false);
	if (last_wildcard_index == -1)
		return (false);
	*pattern_index = last_wildcard_index + 1;
	*str_index = ++(*resume_match_idx);
	return (true);
}

static bool	ft_match_pattern_loop(const char *pattern, const char *str,
		int *pattern_index, int *str_index)
{
	int	last_wildcard_index;
	int	resume_match_idx;

	if (!pattern || !str || !pattern_index || !str_index)
		return (false);
	last_wildcard_index = -1;
	resume_match_idx = 0;
	while (str[*str_index])
	{
		if (ft_match_exact_char(pattern, str, pattern_index, str_index))
			continue ;
		else if (pattern[*pattern_index] == WILDCARD_CHARACTER)
		{
			ft_handle_wildcard(pattern_index, str_index, &last_wildcard_index,
				&resume_match_idx);
		}
		else if (!ft_backtrack_to_wildcard(pattern_index, str_index,
				last_wildcard_index, &resume_match_idx))
		{
			return (false);
		}
	}
	return (true);
}

/**
 * @brief Checks if a string matches a given wildcard pattern.
 *
 * This function supports simple wildcard matching with the '*' character.
 * The wildcard character matches zero or more arbitrary characters.
 *
 * Examples:
 * - `*.txt` matches `file.txt`, `data.txt`
 * - `test*` matches `test`, `test.c`, `testing`
 * - `*file*` matches `myfile.txt`, `file`, `testfile.c`
 * - `file*.txt` matches `file1.txt`, `file2.txt`
 *
 * @param pattern The pattern string containing literal characters and
 *                optional wildcard(s).
 * @param str     The string (e.g. filename) to check against the pattern.
 *
 * @return `true` if the string matches the pattern, `false` otherwise.
 * @see ft_resolve_wildcard_pattern
 */
bool	ft_check_wildcard_pattern(const char *pattern, const char *str)
{
	int	pattern_index;
	int	str_index;

	if (!pattern || !str)
		return (false);
	pattern_index = 0;
	str_index = 0;
	if (!ft_match_pattern_loop(pattern, str, &pattern_index, &str_index))
		return (false);
	while (pattern[pattern_index] == WILDCARD_CHARACTER)
		pattern_index++;
	return (pattern[pattern_index] == '\0');
}
