/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:22:24 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:32:27 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointers(void *memory_address, t_flags *flags)
{
	int	len;
	int	mem_len;

	len = 0;
	if (memory_address)
		mem_len = ft_number_length((uintptr_t)memory_address, 16) + 2;
	else
		mem_len = 5;
	if (flags->width > mem_len)
	{
		if (flags->minus)
		{
			len += ft_format_pointer_address(memory_address, flags);
			len += ft_add_padding(' ', flags->width - len, flags->fd);
		}
		else
		{
			len += ft_add_padding(' ', flags->width - mem_len, flags->fd);
			len += ft_format_pointer_address(memory_address, flags);
		}
	}
	else
		len += ft_format_pointer_address(memory_address, flags);
	return (len);
}
