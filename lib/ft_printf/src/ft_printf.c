/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:45:58 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:41:10 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, const char *str, ...)
{
	int		i;
	int		len;
	va_list	args_list;

	if (!str)
		return (-1);
	va_start(args_list, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == '%') && (str[i + 1] != '\0'))
		{
			len += ft_parse(&str[i + 1], &args_list, &i, fd);
		}
		else
			len += ft_putchar(str[i], fd);
		i++;
	}
	va_end(args_list);
	return (len);
}
