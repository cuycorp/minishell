/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:07:59 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/23 14:08:02 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_home_path(t_shell *data)
{
	char	*home_path;

	if (!data)
		return (NULL);
	home_path = ft_expand_var("HOME", data);
	if (!home_path)
		return (NULL);
	return (home_path);
}

char	*get_new_dir(int len, t_shell *data, t_command *command)
{
	char	*new_dir;

	if (len == 1)
		new_dir = ft_get_home_path(data);
	else
		new_dir = ft_strdup(command->args[1]);
	if (!new_dir)
		return (NULL);
	return (new_dir);
}
