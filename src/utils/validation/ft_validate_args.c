/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:12:57 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/22 09:23:53 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_validate_args(int argc)
{
	if (argc > 1)
	{
		ft_putstr_fd("Usage: ./minishell\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
