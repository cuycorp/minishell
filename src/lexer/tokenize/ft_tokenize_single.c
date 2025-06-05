/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_single.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:27:50 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/03 15:28:26 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_single(char *str, unsigned int *pos, t_shell *data)
{
	if (str[*pos] == '|')
		ft_tokenize_pipe(pos, data);
	else if (str[*pos] == '$')
		ft_tokenize_expansion(str, pos, data);
}
