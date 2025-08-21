/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_var_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:07:44 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/20 17:07:46 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether a given variable declaration string is a valid shell
 * variable name.
 *
 * This function validates a variable name according to shell rules:
 * - It cannot be `NULL` or empty.
 * - It cannot start with "`=`".
 * - The first character must be an alphabetic character (`A-Z`, `a-z`) or an
 * underscore (`_`).
 * - Subsequent characters must be alphanumeric (`A-Z`, `a-z`, `0-9`) or
 * underscores (`_`).
 * - If an invalid character is found, an error message is printed to
 * `STDERR_FILENO`.
 *
 * The function also uses the integer pointer `j` as an index while parsing
 * the string.
 * On return, `*j` will point to the index of either the end of the variable
 * name
 * or the `=` sign (if present).
 *
 * @param[in]  var_declaration  The string containing the variable declaration
 * (e.g., "VAR=value").
 * @param[in,out] j             A pointer to an integer representing the
 * current parsing index.
 *                              It will be incremented during validation.
 *
 * @return `true` if the variable name is valid, `false` otherwise.
 */

bool	ft_is_valid_var_name(char *var_declaration, int *j)
{
	if (!var_declaration)
		return (false);
	if (!ft_strncmp(var_declaration, "_=", 2))
		return (false);
	if (ft_strlen(var_declaration) == 0)
		return (ft_printf(STDERR_FILENO,
				"export: `': not a valid identifier\n"), false);
	if (var_declaration[*j] == '=')
		return (ft_printf(STDERR_FILENO,
				"export: =: not a valid identifier\n"), false);
	while (var_declaration[*j] && var_declaration[*j] != '=')
	{
		if (*j == 0 && !(ft_isalpha(var_declaration[*j])
				|| var_declaration[*j] == '_'))
			return (ft_printf(STDERR_FILENO,
					"export: %s : not a valid identifier\n", var_declaration),
				false);
		else if (!(ft_isalnum(var_declaration[*j])
				|| var_declaration[*j] == '_' ))
			return (ft_printf(STDERR_FILENO,
					"export: %s : not a valid identifier\n", var_declaration),
				false);
		(*j)++;
	}
	return (true);
}
