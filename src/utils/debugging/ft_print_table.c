/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:12:48 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/09 14:12:51 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_table(char **str)
{
	int	k;

	k = 0;
	if (!str)
		return ;
	while (str[k])
	{
		ft_printf(STDOUT_FILENO, "%s\n", str[k]);
		k++;
	}
}
