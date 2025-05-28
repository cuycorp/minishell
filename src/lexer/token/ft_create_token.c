/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:41:28 by jg                #+#    #+#             */
/*   Updated: 2025/05/28 15:38:18 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new token with a given string value and type.
 *
 * Allocates memory for a new token, duplicates the input string
 * and initializes the token type and next pointer.
 *
 * @param str The string value to be duplicated for the token.
 * @param type The type of the token.
 * @return Pointer to the newly created token on success, or NULL on failure.
 */
t_token	*ft_create_token(char *str, t_token_type type)
{
	t_token	*token;

	if (!str || type < 0)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(str);
	if (!token->value)
		return (NULL);
	token->type = type;
	token->next = NULL;
	return (token);
}
