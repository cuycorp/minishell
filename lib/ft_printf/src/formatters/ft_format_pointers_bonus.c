/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_pointers_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:34:21 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:36:06 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Prints a memory address in hexadecimal format.
 *
 * @param memory_address The memory address to be printed.
 *
 * This function prints the given memory address in hexadecimal format,
 * prefixed with "0x". If the pointer is null, it prints "(nil)".
 *
 * @return The total number of characters printed.
 */
int	ft_format_pointer_address(void *memory_address, t_flags *flags)
{
	int			len;
	uintptr_t	address;

	len = 0;
	if (!memory_address)
		return (ft_putstr("(nil)", flags->fd));
	address = (uintptr_t)memory_address;
	len += ft_putstr("0x", flags->fd);
	len += ft_putunbr(address, 16, "0123456789abcdef", flags);
	return (len);
}
