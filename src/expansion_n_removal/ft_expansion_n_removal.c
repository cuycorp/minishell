/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_n_removal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:40:17 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/30 16:34:48 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: not clear what the function does
// static void	ft_end_if_malloc_failure(char *prompt, t_token **token_list,
// 		t_shell *data, bool (*f)(t_token **, t_shell *))
// {
// 	if (f && !f(token_list, data))
// 	{
// 		return (free(prompt), ft_close_program(data, EXIT_FAILURE));

// 	}
// }


/*todo : remove prints*/
bool	ft_expansion_n_removal(t_shell *data)
{
	if (!data)
		return (false);
	if (!ft_evaluate_var_expansion(&data->tokens_list, data))
		return (false);
	if (!ft_retokenize(data))
		return (false);
	if (!ft_quote_removal(&data->tokens_list))
		return (false);
	return (true);
}

