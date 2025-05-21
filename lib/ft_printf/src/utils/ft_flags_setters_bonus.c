/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_setters_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:14:59 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:19:40 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	ft_initialise_flags(void)
{
	t_flags	flags;

	flags.minus = 0;
	flags.zero = 0;
	flags.period = 0;
	flags.precision = 0;
	flags.hashtag = 0;
	flags.space = 0;
	flags.plus = 0;
	flags.star = 0;
	flags.width = 0;
	flags.fd = -1;
	return (flags);
}

void	ft_set_flag_period(t_flags *flags)
{
	flags->period = 1;
	flags->precision = 0;
	flags->zero = 0;
}

void	ft_set_flag_star(t_flags *flags, va_list *args_list)
{
	flags->star = 1;
	if (flags->period)
	{
		flags->precision = va_arg(*args_list, int);
		if (flags->precision < 0)
			flags->precision = -1;
	}
	else
	{
		flags->width = va_arg(*args_list, int);
		if (flags->width < 0)
		{
			flags->minus = 1;
			flags->width = -flags->width;
		}
	}
}

void	ft_set_digits(char c, t_flags *flags)
{
	if (flags->period)
		flags->precision = (flags->precision * 10) + (c - '0');
	else
		flags->width = (flags->width * 10) + (c - '0');
}

void	ft_set_flag_minus(t_flags *flags)
{
	flags->minus = 1;
	flags->zero = 0;
}
