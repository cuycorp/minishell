/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_locate_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:46:49 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/23 13:46:52 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_locate_var(char *str, int *i)
{
	int	start;
	int	length;

	start = 0;
	length = 0;
	while (str[*i])
	{
		if (str[*i] == '$')
		{
			(*i)++;
			start = *i;
			while ((ft_isalnum(str[*i]) || str[*i] == '_') && str[*i])
				(*i)++;
			length = *i - start;
			return (ft_substr(str, start, length));
		}
		else
			(*i)++;
	}
	return (0);
}
