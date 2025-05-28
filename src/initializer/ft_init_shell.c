/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:04:03 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/27 22:11:26 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*ft_init_shell(void)
{
	t_shell	*shell;

	shell = (t_shell *)ft_alloc_struct(sizeof(t_shell));
	if (!shell)
		return (NULL);

	return (shell);
}
