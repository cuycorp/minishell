/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:32:06 by jgossard          #+#    #+#             */
/*   Updated: 2025/03/14 16:11:15 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sanitize_base(char *base)
{
	int		i;
	int		j;
	size_t	base_len;

	i = 0;
	base_len = ft_strlen(base);
	if (base_len <= 1)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] <= ' ')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*
** Convert a char from base to decimal base
** if char c is not included in base, return -1
*/
int	ft_int_convert(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief	Converts a string representation of a number in a given base to
 * 			an integer.
 *
 * This function takes a string `str` representing a number in the given `base`
 * and converts it to an integer. It handles leading whitespace, optional `+`
 * or `-` signs, and validates the base.
 *
 * @param str The string containing the number to convert.
 * @param base The string representing the valid characters of the base.
 * @return The integer representation of `str` in the given `base`.
 *         Returns `0` if the base is invalid.
 */
int	ft_atoi_base(char *str, char *base)
{
	int			i;
	int			sign;
	long int	result;
	size_t		base_len;

	if (!ft_sanitize_base(base))
		return (0);
	base_len = ft_strlen(base);
	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_int_convert(str[i], base) != -1)
	{
		result = result * base_len + ft_int_convert(str[i], base);
		i++;
	}
	return (result * sign);
}
