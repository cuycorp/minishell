/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:56:36 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/07 17:00:36 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_value(char *key, char **envp)
{
	char	*env;
	int		env_len;
	int		i;

	if (!key || !envp)
		return (NULL);
	env = NULL;
	env_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, env_len) == 0
			&& envp[i][env_len] == EQUAL_SIGN)
		{
			env = ft_substr(envp[i], env_len + EQUAL_SIGN_LEN,
					ft_strlen(envp[i]) - env_len - 1);
			if (!env)
				return (NULL);
			break ;
		}
		i++;
	}
	return (env);
}
