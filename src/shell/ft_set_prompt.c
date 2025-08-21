/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:33:25 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/21 15:38:15 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_set_prompt(t_shell *data)
{
	char	*prompt;
	int		i;
	char	*pwd;
	char	*equal_sign;

	if (!data)
		return (NULL);
	i = 0;
	while (data->ev[i] && ft_strncmp(data->ev[i], "PWD=",
			ft_strlen("PWD=")) != 0)
		i++;
	if (!data->ev[i])
		return (ft_strdup(PROMPT));
	equal_sign = ft_strchr(data->ev[i], '=');
	if (!equal_sign)
		return (ft_strdup(PROMPT));
	pwd = equal_sign + 1;
	prompt = ft_strjoin(pwd, PROMPT);
	return (prompt);
}
