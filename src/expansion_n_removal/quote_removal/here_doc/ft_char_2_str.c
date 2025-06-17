/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_2_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:22:43 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/22 12:22:45 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_char_2_str(char c)
{
	char	*result;

	result = ft_alloc_struct(2 * sizeof(char));
	if (!result)
		return (NULL);
	result[0] = c;
	result[1] = '\0';
	return (result);
}
