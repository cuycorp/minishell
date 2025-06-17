/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_single_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:59:43 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/22 13:59:46 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_len_single_quoted_section(char *str, int *i)
{
	int len;
	int start;
	char c;

	if (!str)
		return (-1);
	start = *i;
	c = str[*i];
	(*i)++; //skip leading single quote
	while(str[*i])
	{
		c = str[*i];
		printf("%c", c);
		if (str[*i] == '\'')
		{
			(*i)++; // skip closing single quote
			break;
		}
		(*i)++;
	}
	len = *i - start;
	return (len);
}


char *ft_extract_single_quoted_str(char *str, int *i)
{
	int len;
	int start;
	char *single;

	if (!str)
		return (NULL);
	start = *i;
	len = ft_len_single_quoted_section(str, i);
	single = ft_substr(str, start, len);
	if(!single)
		return (NULL);
	return(single);
}
