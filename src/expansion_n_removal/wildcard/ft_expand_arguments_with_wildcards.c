/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_arguments_with_wildcards.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 22:46:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/11 14:01:01 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Appends a single match from a wildcard expansion to the result list.
 *
 * This function appends the item at index @p *match_index from the
 * @p expanded_items array to the @p expanded_args array.
 *
 * @param expanded_items   The list of strings matched by the wildcard pattern.
 * @param expanded_args    Pointer to the array collecting expanded arguments.
 *
 * @param expanded_count   Pointer to the number of currently expanded arguments
 * @param match_index      Pointer to the index of the current match to add.
 *
 * @return true on success, false if appending fails.
 */
static bool	ft_add_wildcard_matches_to_expanded_args(char **expanded_items,
		char ***expanded_args, int *expanded_count, int *item_index)
{
	if (!expanded_items || !expanded_args || !item_index)
		return (false);
	if (!ft_append_to_string_array(expanded_args, expanded_count,
			expanded_items[*item_index]))
	{
		ft_printf(STDERR_FILENO,
			"Minishell: ft_append_to_string_array failed:%$\n",
			strerror(errno));
		return (false);
	}
	return (true);
}

/**
 * @brief Expands a single wildcard-containing argument and appends matches.
 *
 * This function is called only if the argument at @p *arg_index contains
 * a wildcard. It resolves the pattern into matching items and appends
 * them to the expanded argument list.
 *
 * @param args            The original argument list.
 * @param expanded_args   Pointer to the current list of expanded arguments.
 * @param expanded_count  Pointer to the count of expanded arguments.
 * @param arg_index       Pointer to the index of the argument to process.
 *
 * @return true on success, false on memory allocation error.
 */
static bool	ft_process_wildcard_expansion(char **input_args,
		char ***expanded_args, int *expanded_count, int *current_arg_indx)
{
	int		item_index;
	char	**expanded_items;

	if (!input_args || !current_arg_indx)
		return (false);
	// Expand this wildcard argument
	expanded_items = ft_resolve_wildcard_pattern(input_args[*current_arg_indx]);
	if (!expanded_items)
		return (ft_free_char_tab(expanded_items), false);
	// if expanded argument OK
	item_index = 0;
	while (expanded_items[item_index])
	{
		// Add all matches to expanded_args
		if (!ft_add_wildcard_matches_to_expanded_args(expanded_items,
				expanded_args, expanded_count, &item_index))
			return (ft_free_char_tab(expanded_items), false);
		item_index++;
	}
	ft_free_char_tab(expanded_items);
	return (true);
}

static void	ft_init_expansion_state(char ***expanded_args,
		int *current_arg_index, int *expanded_args_count)
{
	*expanded_args = NULL;
	*current_arg_index = 0;
	*expanded_args_count = 0;
}

/**
 * @brief Expands command-line arguments containing wildcard patterns.
 *
 * This function iterates over a NULL-terminated array of strings (arguments).
 * If an argument contains a wildcard character (e.g., '*'), it is expanded to
 * match the actual filenames in the current directory using pattern matching.
 * If an argument has no wildcard, it is copied as-is.
 *
 * For example:
 * - Input: {"*.c", "Makefile"}
 * - Output: {"main.c", "utils.c", "Makefile"} (if those files exist)
 *
 * Internally uses:
 * - `ft_has_wildcard` to detect patterns
 * - `ft_resolve_wildcard_pattern` to expand them
 * - `ft_append_to_string_array` to accumulate results
 *
 * @param args The original argument list (NULL-terminated array of strings).
 *
 * @return A newly allocated array of strings with expanded arguments,
 *			or NULL if a memory allocation fails.
 *			The caller is responsible for freeing the returned array.
 *
 * @see ft_has_wildcard
 * @see ft_resolve_wildcard_pattern
 * @see ft_append_to_string_array
 */
char	**ft_expand_arguments_with_wildcards(char **input_args)
{
	char	**expanded_args;
	int		current_arg_index;
	int		expanded_args_count;

	if (!input_args || !*input_args)
		return (NULL);
	ft_init_expansion_state(&expanded_args, &current_arg_index,
		&expanded_args_count);
	while (input_args[current_arg_index])
	{
		if (ft_has_wildcard(input_args[current_arg_index]))
		{
			if (!ft_process_wildcard_expansion(input_args, &expanded_args,
					&expanded_args_count, &current_arg_index))
				return (ft_free_char_tab(expanded_args), NULL);
		}
		else
		{
			if (!ft_append_to_string_array(&expanded_args, &expanded_args_count,
					input_args[current_arg_index]))
				return (ft_free_char_tab(expanded_args), NULL);
		}
		current_arg_index++;
	}
	return (expanded_args);
}
