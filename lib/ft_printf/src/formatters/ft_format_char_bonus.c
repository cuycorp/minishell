/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_char_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:49:27 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:29:24 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_char_with_flags(char c, t_flags *flags)
{
	int	len;
	int	char_len;

	len = 0;
	char_len = 1;
	if (flags->minus == 1)
	{
		len += ft_putchar(c, flags->fd);
		len += ft_add_padding(' ', flags->width - len, flags->fd);
	}
	else
	{
		len += ft_add_padding(' ', flags->width - char_len, flags->fd);
		len += ft_putchar(c, flags->fd);
	}
	return (len);
}
