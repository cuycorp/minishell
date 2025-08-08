/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:32:07 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/07 18:32:08 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_verify_limits(long long sign, long long result, long long digit,
		bool *is_valid_num)
{
	if (sign == 1 && result > (LLONG_MAX - digit) / 10)
	{
		*is_valid_num = false;
		return (false);
	}
	if (sign == -1 && -result < (LLONG_MIN + digit) / 10)
	{
		*is_valid_num = false;
		return (false);
	}
	return (true);
}

long long	ft_atoll(const char *nptr, bool *is_valid_num)
{
	long long	i;
	long long	sign;
	long long	result;
	long long	digit;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if ((nptr[i] == '+') || (nptr[i] == '-'))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		digit = nptr[i] - '0';
		if (!ft_verify_limits(sign, result, digit, is_valid_num))
			return (0);
		result = result * 10 + digit;
		i++;
	}
	return (result * sign);
}
