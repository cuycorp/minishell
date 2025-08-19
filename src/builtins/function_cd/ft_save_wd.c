/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_wd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:51:54 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/19 12:51:57 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_save_wd(char *variable)
{
	if (!getcwd(variable, PATH_MAX))
		return (false);
	return (true);
}
