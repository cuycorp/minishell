/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_wildcard_context.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:17:36 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/13 15:47:28 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_matches_array(t_wildcard_context *context)
{
	if (context && context->matches)
	{
		ft_free_char_tab(context->matches);
		context->matches = NULL;
	}
}

void	ft_free_wildcard_context(t_wildcard_context *context)
{
	if (!context)
		return ;
	if (context->directory)
	{
		closedir(context->directory);
		context->directory = NULL;
	}
	ft_free_matches_array(context);
	if (context->pattern)
	{
		free(context->pattern);
		context->pattern = NULL;
	}
	if (context->directory_part)
	{
		free(context->directory_part);
		context->directory_part = NULL;
	}
	if (context->basename_part)
	{
		free(context->basename_part);
		context->basename_part = NULL;
	}
	free(context);
}
