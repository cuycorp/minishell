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

