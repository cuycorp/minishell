/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:04:03 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 14:19:51 by jgossard         ###   ########.fr       */
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
		if (!envp[i])
			return (ft_free_char_tab(ev), NULL);
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
	shell->infile = -1; // TODO: to keep?
	shell->exit_code = -1;
	shell->pid_count = 0;
	shell->command_count = 0;
	// shell->log_fd = open("logs.txt", O_WRONLY | O_CREAT | O_TRUNC,
	// 			STANDARD_FILE_PERMISSIONS); // TODO: to remove
	return (shell);
}
