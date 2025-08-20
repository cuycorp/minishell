/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_var_definition.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:15:54 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/20 18:15:57 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_set_var_definition(char *arguments, int *j, int *to_env)
{
	char	*var_definition;
	char	*var_name;

	if (!arguments)
		return (false);
	var_name = ft_substr(arguments, 0, *j);
	if (!var_name)
		return (NULL);
	if (arguments[*j] == '=')
	{
		*to_env = 1;
		var_definition = ft_strjoin(var_name, &arguments[*j]);
		if (!var_definition)
			return (free(var_name), NULL);
		return (free(var_name), var_definition);
	}
	else
		return (var_name);
}
