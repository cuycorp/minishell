/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_parent_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:07:40 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 11:13:18 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_parent_builtin(char *command_name)
{
	if (!command_name)
		return (false);
	return (ft_strncmp(command_name, CD, ft_strlen(CD)) == 0
		|| ft_strncmp(command_name, EXPORT, ft_strlen(EXPORT)) == 0
		|| ft_strncmp(command_name, UNSET, ft_strlen(UNSET)) == 0
		|| ft_strncmp(command_name, EXIT, ft_strlen(EXIT)) == 0);
}
