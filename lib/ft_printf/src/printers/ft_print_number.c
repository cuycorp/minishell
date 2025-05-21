/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:34:07 by jgossard          #+#    #+#             */
/*   Updated: 2025/01/02 16:13:15 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_nbr(long int number, int base, char *base_chars, t_flags *f)
{
	return (format_number(number, base, base_chars, f));
}

int	ft_print_unbr(unsigned int number, int base, char *base_chars, t_flags *f)
{
	return (format_unumber(number, base, base_chars, f));
}
