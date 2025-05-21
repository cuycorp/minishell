/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:10:51 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:34:00 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_number_length(long number, int base)
{
	int	len;

	len = 1;
	if (number < 0)
	{
		number = -number;
		len++;
	}
	while (number >= base)
	{
		number /= base;
		len++;
	}
	return (len);
}

int	handle_sign(int sign, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->plus && sign == 0)
		len += ft_putchar('+', flags->fd);
	else if (flags->space && sign == 0)
		len += ft_putchar(' ', flags->fd);
	return (len);
}

int	handle_special_case(long int number, t_flags *flags)
{
	int	len;

	len = 0;
	if (number == 0 && flags->period && flags->precision == 0)
	{
		len += ft_add_padding(' ', flags->width, flags->fd);
	}
	return (len);
}

int	set_sign_minus(int sign, int fd)
{
	int	len;

	len = 0;
	if (sign)
		len += ft_putchar('-', fd);
	return (len);
}
