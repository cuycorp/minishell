/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:40:58 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:17:56 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr(const char *str, int fd)
{
	int	strlen;
	int	i;

	if (!str)
		str = "(null)";
	i = 0;
	strlen = 0;
	while (str[i])
	{
		strlen += ft_putchar(str[i], fd);
		i++;
	}
	return (strlen);
}

int	ft_putnstr(const char *str, int n, int fd)
{
	int	i;

	i = 0;
	while (str[i] && i < n)
	{
		ft_putchar(str[i], fd);
		i++;
	}
	return (i);
}
