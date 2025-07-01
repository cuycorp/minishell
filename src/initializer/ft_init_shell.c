/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:04:03 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 19:34:04 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static char	**ft_set_env(char **envp)
{
	char	**ev;
	int		i;
	int		len_env;

	i = 0;
	len_env = ft_len_env(envp);
	ev = (char **)malloc((len_env + 1) * sizeof(char *));
	if (!ev)
		return (NULL);
	while (i < len_env)
	{
		ev[i] = ft_strdup(envp[i]);
		if (!ev[i])
			return (ft_free_char_tab(ev), NULL);
		i++;
	}
	ev[len_env] = NULL;
	return (ev);
}

t_shell	*ft_init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)ft_alloc_struct(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->ev = ft_set_env(envp);
	return (shell);
}
