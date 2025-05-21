/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:53:43 by jgossard          #+#    #+#             */
/*   Updated: 2024/12/02 19:21:01 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Counts the number of digits in a number, including the sign
 * 			for negative numbers.
 *
 * @param nb The number to count the digits of.
 * @return The number of digits in the number.
 */
static size_t	ft_count_digits(long nb)
{
	size_t	count;

	count = 1;
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

/**
 * @brief Converts an integer to a null-terminated string.
 *
 * This function allocates memory for the resulting string, which must be freed
 * by the caller.
 *
 * @param nbr The integer to convert.
 * @return A pointer to the newly allocated string, or NULL if the allocation
 *  fails.
 */
char	*ft_itoa(int nbr)
{
	char	*str;
	size_t	digits_number;
	long	number;

	number = (long)nbr;
	digits_number = ft_count_digits(number);
	str = (char *)malloc((digits_number + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[digits_number] = '\0';
	if (number == 0)
		str[0] = '0';
	if (number < 0)
	{
		str[0] = '-';
		number = -number;
	}
	while (number > 0)
	{
		str[--digits_number] = (number % 10) + '0';
		number /= 10;
	}
	return (str);
}
