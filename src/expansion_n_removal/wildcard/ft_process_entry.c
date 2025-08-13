/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_entry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:43:25 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/13 09:46:50 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_build_path(const char *directory, const char *filename)
{
	char	*result;
	size_t	directory_len;
	size_t	filename_len;
	size_t	total_len;
	bool	need_slash;

	if (!directory || !filename)
		return (NULL);
	if (directory[0] == '.' && directory[1] == '\0')
		return (ft_strdup(filename));
	directory_len = ft_strlen(directory);
	filename_len = ft_strlen(filename);
	need_slash = (directory_len > 0
		&& (directory[directory_len - 1] != SLASH_CHARACTER));
	total_len = directory_len + filename_len + 1;
	if (need_slash)
		total_len++;
	result = malloc(sizeof(char) * total_len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, directory, total_len);
	if (need_slash)
		ft_strlcat(result, "/", total_len);
	ft_strlcat(result, filename, total_len);
	return (result);
}

bool	ft_process_entry(t_wildcard_context *context)
{
	const char	*filename;
	char		*full_path;

	if (!context || !context->entry)
		return (false);
	filename = context->entry->d_name;
	if (filename[0] != DOT_CHARACTER
		|| (context->basename_part[0] == DOT_CHARACTER))
	{
		if (ft_check_wildcard_pattern(context->basename_part, filename))
		{
			full_path = ft_build_path(context->directory_part,
				context->entry->d_name);
			if (!full_path)
				return (false);
			if (!ft_append_to_string_array(&context->matches,
					&context->match_count, full_path))
			{
				free(full_path);
				return (false);
			}
			free(full_path);
		}
	}
	return (true);
}
