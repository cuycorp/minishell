/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_number_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:23:50 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/12 13:42:10 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_sign_and_pad(int sign, int numlen, int pad, t_flags *f)
{
	int	len;

	len = 0;
	len += handle_sign(sign, f);
	if (f->minus)
	{
		len += set_sign_minus(sign, f->fd);
		len += ft_add_padding('0', pad, f->fd);
	}
	else
	{
		if (f->zero && !f->period)
		{
			len += set_sign_minus(sign, f->fd);
			len += ft_add_padding('0', f->width - (numlen + pad + sign), f->fd);
		}
		else
		{
			len += ft_add_padding(' ', f->width - (numlen + pad + sign), f->fd);
			len += set_sign_minus(sign, f->fd);
		}
		len += ft_add_padding('0', pad, f->fd);
	}
	return (len);
}

int	format_number(long int number, int base, char *base_chars, t_flags *f)
{
	int	len;
	int	num_len;
	int	padding;
	int	sign;

	len = 0;
	sign = (number < 0);
	num_len = ft_number_length(number, base) - sign;
	padding = handle_padding(num_len, f->precision);
	len += handle_special_case(number, f);
	if (len > 0)
		return (len);
	len += handle_sign_and_pad(sign, num_len, padding, f);
	len += ft_putnbr(number, base, base_chars, f);
	if (f->minus)
		len += ft_add_padding(' ',
				f->width - (num_len + padding + sign),
				f->fd);
	return (len);
}

int	format_unumber(unsigned int number, int base, char *base_chars, t_flags *f)
{
	int	len;
	int	num_len;
	int	padding;

	len = 0;
	num_len = ft_number_length(number, base);
	padding = handle_padding(num_len, f->precision);
	len += handle_special_case(number, f);
	if (len > 0)
		return (len);
	len += ft_handle_hash(number, f, base, base_chars);
	len += handle_sign_and_pad(0, num_len, padding, f);
	len += ft_putunbr(number, base, base_chars, f);
	if (f->minus)
		len += ft_add_padding(' ', f->width - (num_len + padding), f->fd);
	return (len);
}
