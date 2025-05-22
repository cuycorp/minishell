/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:28:04 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/22 09:56:52 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_shell(void)
{
	char	*input;

	while (1)
	{
		input = readline("Oh-My-Shell > ");
		if (!input)
			break;
		if (ft_strncmp(input, "exit", ft_strlen("exit")) == 0)
		{
			ft_putstr_fd(input, STDOUT_FILENO);
			free(input);
			break;
		}
		else
			ft_printf(STDOUT_FILENO, "%s\n", input);
		free(input);
	}

}
