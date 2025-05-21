/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_string_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:23:06 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:32:01 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Formats a string with specified padding and alignment.
 *
 * This function formats a string by adding padding and aligning it based on
 * the provided flags.
 * If the minus flag is set, the string is left-aligned,
 * otherwise it is right-aligned.
 *
 * @param str The string to be formatted.
 * @param str_len The length of the string to be printed.
 * @param padding The number of padding characters to be added.
 * @param f Pointer to the t_flags structure containing formatting flags.
 * @return The total number of characters printed.
 */
int	format_string_with_padding(char *str, int str_len, int padding, t_flags *f)
{
	int	len;

	len = 0;
	if (f->minus)
	{
		len += ft_putnstr(str, str_len, f->fd);
		len += ft_add_padding(' ', padding, f->fd);
	}
	else
	{
		len += ft_add_padding(' ', padding, f->fd);
		len += ft_putnstr(str, str_len, f->fd);
	}
	return (len);
}
