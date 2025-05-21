/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:57:49 by jgossard          #+#    #+#             */
/*   Updated: 2025/01/05 23:43:14 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_string_with_flags(char *str, t_flags *flags)
{
	int	len;
	int	precision_len;
	int	padding;

	if (!str)
		str = "(null)";
	precision_len = handle_precision(str, flags);
	padding = handle_padding(precision_len, flags->width);
	len = format_string_with_padding(str, precision_len, padding, flags);
	return (len);
}
