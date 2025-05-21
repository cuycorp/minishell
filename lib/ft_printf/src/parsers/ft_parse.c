/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:08:46 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:25:26 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse(const char *str, va_list *args_list, int *index, int fd)
{
	int		i;
	int		len;
	t_flags	flags;

	i = 0;
	len = 0;
	flags = ft_initialise_flags();
	flags.fd = fd;
	while (str[i] && (ft_isflags(str[i]) || ft_isdigit(str[i])))
	{
		ft_parse_flags(str[i], &flags, args_list);
		i++;
		(*index)++;
	}
	if (str[i] && ft_isspecifier(str[i]))
	{
		len += ft_parse_specifier(str[i], args_list, &flags);
		(*index)++;
	}
	return (len);
}
