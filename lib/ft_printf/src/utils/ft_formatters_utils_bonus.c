/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formatters_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:14:02 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:32:48 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_precision(char *str, t_flags *flags)
{
	int		strlen;
	char	*null_str;

	null_str = "(null)";
	strlen = ft_strlen(str);
	if (ft_strncmp(str, null_str, ft_strlen(null_str)) == 0)
	{
		if (flags->period && flags->precision >= 0 && flags->precision < strlen)
			return (0);
		return (strlen);
	}
	if (flags->period && flags->precision >= 0 && flags->precision < strlen)
		return (flags->precision);
	return (strlen);
}

int	ft_add_padding(char c, int padding, int fd)
{
	int	len;

	len = 0;
	while (len < padding)
		len += ft_putchar(c, fd);
	return (len);
}

int	handle_padding(int len, int total_len)
{
	if (total_len > len)
		return (total_len - len);
	return (0);
}

int	ft_handle_hash(unsigned int number, t_flags *f, int base, char *base_chars)
{
	int	len;

	len = 0;
	if (number == 0 && f->period && f->precision == 0)
		return (0);
	if (f->hashtag && number != 0)
	{
		if (base == 16 && base_chars[10] == 'a')
			len += ft_putstr("0x", f->fd);
		else if (base == 16 && base_chars[10] == 'A')
			len += ft_putstr("0X", f->fd);
		else if (base == 8)
			len += ft_putchar('0', f->fd);
	}
	return (len);
}
