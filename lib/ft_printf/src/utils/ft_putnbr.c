/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:40:43 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 20:22:55 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Validates the given base_chars string.
 *
 * @param base_chars The base_chars string to be validated.
 *
 * This function checks if the given base_chars string is valid.
 * A valid base_chars string must have at least two characters, must not contain
 *  '+' or '-' characters, and must not have duplicate characters.
 *
 * @return 1 if the base_chars is valid, 0 otherwise.
 */
static int	ft_sanitize_base(char *base_chars)
{
	int	i;
	int	j;
	int	base_len;

	i = 0;
	base_len = ft_strlen(base_chars);
	if (base_len <= 1)
		return (0);
	while (base_chars[i])
	{
		if (base_chars[i] == '+' || base_chars[i] == '-')
			return (0);
		j = i + 1;
		while (base_chars[j])
		{
			if (base_chars[i] == base_chars[j])
				return (0);
			else
				j++;
		}
		i++;
	}
	return (1);
}

/**
 * @brief Prints a signed number in a specified base.
 * @param number: The signed number to be printed.
 * @param base: The base in which to print the number.
 * @param base_chars: The characters representing the digits of the base.
 *
 * This function prints a signed number in the specified base using the
 * characters provided in base_chars. If the number is negative, it prints
 * a '-' sign before the number. The function returns the total number of
 * characters printed.
 *
 * @return The total number of characters printed.
 */
int	ft_putnbr(long int number, int base, char *base_chars, t_flags *f)
{
	int	len;

	len = 0;
	if (!ft_sanitize_base(base_chars))
		return (len);
	if (number == 0 && f->period && f->precision == 0)
		return (len);
	if (number < 0)
		number = -number;
	if (number >= base)
		len += ft_putnbr((number / base), base, base_chars, f);
	len += ft_putchar(base_chars[number % base], f->fd);
	return (len);
}

/**
 * @brief Prints an unsigned number in a specified base.
 * @param number: The unsigned number to be printed.
 * @param base: The base in which to print the number.
 * @param base_chars: The characters representing the digits of the base.
 *
 * This function prints an unsigned number in the specified base using the
 * characters provided in base_chars. If the number is negative, it prints
 * a '-' sign before the number. The function returns the total number of
 * characters printed.
 *
 * @return The total number of characters printed.
 */
int	ft_putunbr(unsigned long int number, int base, char *base_chars, t_flags *f)
{
	int	len;

	len = 0;
	if (!ft_sanitize_base(base_chars))
		return (len);
	if (number == 0 && f->period && f->precision == 0)
		return (len);
	if (number >= (unsigned long int)base)
		len += ft_putunbr((number / base), base, base_chars, f);
	len += ft_putchar(base_chars[number % base], f->fd);
	return (len);
}
