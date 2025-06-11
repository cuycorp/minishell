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

static char	**ft_set_env(char **envp)
{
	char	**ev;
	int		i;

	i = 0;
	ev = (char **)ft_alloc_struct(52 * sizeof(char *));
	if (!ev)
		return (NULL);
	while (i < 52)
	{
		ev[i] = ft_strdup(envp[i]);
		i++;
	}
	return (ev);
}

t_shell	*ft_init_shell(char **envp)
{
	t_shell	*shell;
	int		i;

	i = 0;
	shell = (t_shell *)ft_alloc_struct(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->ev = ft_set_env(envp);
	return (shell);
}

/*
	printf("printing copy of env\n");
	while (i < 52)
	{
		printf("%s\n", shell->ev[i]);
		i++;
	} */
