/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:08:49 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/30 17:04:28 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_flags(char c, t_flags *flags, va_list *args_list)
{
	if (c == '-')
		ft_set_flag_minus(flags);
	else if ((c == '0') && (!flags->period) \
				&& (flags->width == 0) && (flags->minus == 0))
		flags->zero = 1;
	else if (c == '#')
		flags->hashtag = 1;
	else if (c == ' ')
		flags->space = 1;
	else if (c == '+')
		flags->plus = 1;
	else if (c == '.')
		ft_set_flag_period(flags);
	else if (c == '*')
		ft_set_flag_star(flags, args_list);
	else if (ft_isdigit(c))
		ft_set_digits(c, flags);
	return (1);
}
