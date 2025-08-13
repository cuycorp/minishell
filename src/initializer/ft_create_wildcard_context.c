/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_wildcard_context.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:03:26 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/12 15:31:29 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_wildcard_context	*ft_create_wildcard_context(const char *pattern)
{
	t_wildcard_context	*context;

	if (!pattern)
		return (NULL);
	context = malloc(sizeof(t_wildcard_context));
	if (!context)
		return (NULL);
	context->pattern = ft_strdup(pattern);
	if (!context->pattern)
		return (ft_free_wildcard_context(context), NULL);
	context->directory_part = ft_get_dir_part(context->pattern);
	if (!context->directory_part)
		return (ft_free_wildcard_context(context), NULL);
	context->basename_part = ft_get_basename_part(context->pattern);
	if (!context->basename_part)
		return (ft_free_wildcard_context(context), NULL);
	context->directory = opendir(context->directory_part);
	if (!context->directory)
		return (ft_free_wildcard_context(context), NULL);
	context->matches = NULL;
	context->entry = readdir(context->directory);
	context->match_count = 0;
	return (context);
}
