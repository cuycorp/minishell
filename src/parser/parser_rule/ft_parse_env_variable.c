/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:20:18 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 19:29:16 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_env_variable(t_token **tokens)
{
	char	*env_variable;

	if (!tokens || !(*tokens))
		return (NULL);
	if ((*tokens)->type == TOKEN_EXPANSION)
	{
		env_variable = ft_strdup((*tokens)->value);
		if (!env_variable)
			return (NULL);
		ft_advance_token(tokens);
		return (env_variable);
	}
	return (NULL);
}
