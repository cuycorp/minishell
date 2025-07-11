/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:51:17 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/23 15:37:52 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_char_tab(char **tabs)
{
	int	i;

	if (!tabs || !*tabs)
		return ;
	i = 0;
	while (tabs[i] != NULL)
	{
		ft_printf(STDOUT_FILENO, "tab[%d] = %s\n", i, tabs[i]);
		i++;
	}
}
