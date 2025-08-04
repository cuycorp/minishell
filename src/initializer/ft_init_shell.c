/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:04:03 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/04 10:26:39 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_set_env(char **envp)
{
	char	**ev;
	int		i;
	int		len_env;

	if (!envp || !*envp)
		return (NULL);
	i = 0;
	len_env = ft_len_table(envp);
	if (len_env == 0)
		return (NULL);
	ev = (char **)malloc((len_env + 1) * sizeof(char *));
	if (!ev)
		return (NULL);
	while (i < len_env && envp[i])
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

	if (!envp || !envp[0])
		return (NULL);
	shell = (t_shell *)ft_alloc_struct(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->ev = ft_set_env(envp);
	if (shell->ev == NULL)
		return (ft_clear_memory(shell), NULL);
	shell->export = ft_set_env(envp);
	if (shell->export == NULL)
		return (ft_clear_memory(shell), NULL);
	shell->exit_code = 0;
	return (shell);
}
