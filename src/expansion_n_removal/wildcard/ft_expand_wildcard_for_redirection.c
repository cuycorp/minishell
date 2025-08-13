/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_wildcard_for_redirection.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:30:37 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/13 13:07:17 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_validate_redir_matches(t_token *current, int count,
	t_shell *data)
{
	if (!current || !data)
		return (false);
	if (count == 0)
	{
		ft_printf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			current->value);
		data->exit_code = 1;
		data->has_raised_error = true;
		return (true);
	}
	if (count > 1)
	{
		ft_printf(STDERR_FILENO, "minishell: %s: ambiguous redirect\n",
			current->value);
		data->exit_code = 1;
		data->has_raised_error = true;
		return (false);
	}
	return (true);
}

static bool	ft_redir_replace_value(t_token *current, char *match)
{
	if (!current || !match)
		return (false);
	free(current->value);
	current->value = ft_strdup(match);
	if (!current->value)
		return (false);
	return (true);
}

bool	ft_expand_wildcard_for_redirection(t_token *current, t_shell *data)
{
	char	**matches;
	int		count;

	if (!current || !data)
		return (false);
	matches = ft_resolve_wildcard_pattern(current->value, data);
	if (!matches)
		return (false);
	count = ft_len_table(matches);
	if (!ft_validate_redir_matches(current, count, data))
		return (ft_free_char_tab(matches), false);
	if (!ft_redir_replace_value(current, matches[0]))
		return (ft_free_char_tab(matches), false);
	ft_free_char_tab(matches);
	return (true);
}
