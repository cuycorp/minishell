/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:17:49 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/14 19:17:51 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_append_char(char *str, char c)
{
	char	*final;
	char	*char_str;

	if (!str)
		return (NULL);
	char_str = ft_char_2_str(c);
	if (!char_str)
		return (NULL);
	final = ft_strjoin(str, char_str);
	free(char_str);
	if (!final)
		return (free(str), NULL);
	return (free(str), final);
}
