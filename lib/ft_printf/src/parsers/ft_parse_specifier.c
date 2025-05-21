/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_specifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:08:05 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:20:15 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_specifier(char c, va_list *args_list, t_flags *flags)
{
	if (c == 'c')
		return (ft_print_char_with_flags(va_arg(*args_list, int), flags));
	else if (c == 's')
		return (ft_print_string_with_flags(va_arg(*args_list, char *), flags));
	else if (c == 'p')
		return (ft_print_pointers(va_arg(*args_list, void *), flags));
	else if (c == 'd' || c == 'i')
		return (ft_print_nbr(va_arg(*args_list, int), BASE_10, \
		DECIMAL_DIGITS, flags));
	else if (c == 'u')
		return (ft_print_unbr(va_arg(*args_list, unsigned int), BASE_10, \
		DECIMAL_DIGITS, flags));
	else if (c == 'x')
		return (ft_print_unbr(va_arg(*args_list, unsigned int), BASE_16, \
		LOWER_HEXA_DIGITS, flags));
	else if (c == 'X')
		return (ft_print_unbr(va_arg(*args_list, unsigned int), BASE_16, \
		UPPER_HEXA_DIGITS, flags));
	else if (c == '%')
		return (ft_putchar('%', flags->fd));
	return (0);
}
