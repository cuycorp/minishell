/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:57:01 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/04 15:02:26 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_child(t_shell *data, int exit_code)
{
	if (!data)
		exit(EXIT_FAILURE);
	if (data)
		ft_clear_memory(data);
	exit(exit_code);
}
