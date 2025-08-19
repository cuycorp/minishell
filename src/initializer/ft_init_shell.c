/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:04:03 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 17:15:33 by jgossard         ###   ########.fr       */
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

static char	**ft_set_env2(void)
{
	char	**ev;
	int		len_env;
	char	path[PATH_MAX];

	len_env = 3;
	ev = (char **)malloc((len_env + 1) * sizeof(char *));
	if (!ev)
		return (NULL);
	ft_save_wd(path);
	ev[0] = ft_strjoin("PWD=", path);
	if (!ev[0])
		return (ft_free_char_tab(ev), NULL);
	ev[1] = ft_strdup("SHLVL=1");
	if (!ev[1])
		return (ft_free_char_tab(ev), NULL);
	ev[2] = ft_strdup("_=/usr/bin/env");
	if (!ev[2])
		return (ft_free_char_tab(ev), NULL);
	ev[len_env] = NULL;
	return (ev);
}

static char	**ft_set_exp2(void)
{
	char	**ev;
	int		len_env;
	char	path[PATH_MAX];

	len_env = 3;
	ev = (char **)malloc((len_env + 1) * sizeof(char *));
	if (!ev)
		return (NULL);
	ft_save_wd(path);
	ev[0] = ft_strdup("OLDPWD");
	if (!ev[0])
		return (ft_free_char_tab(ev), NULL);
	ev[1] = ft_strjoin("PWD=", path);
	if (!ev[1])
		return (ft_free_char_tab(ev), NULL);
	ev[2] = ft_strdup("SHLVL=1");
	if (!ev[2])
		return (ft_free_char_tab(ev), NULL);
	ev[len_env] = NULL;
	return (ev);
}

static bool	ft_set_env_i(t_shell *shell)
{
	shell->ev = ft_set_env2();
	if (shell->ev == NULL)
		return (ft_clear_memory(shell), false);
	shell->export = ft_set_exp2();
	if (shell->export == NULL)
		return (ft_clear_memory(shell), false);
	return (true);
}

t_shell	*ft_init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)ft_alloc_struct(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->exit_code = 0;
	shell->has_raised_error = false;
	if (!envp || !envp[0])
	{
		if (!ft_set_env_i(shell))
			return (NULL);
	}
	else
	{
		shell->ev = ft_set_env(envp);
		if (shell->ev == NULL)
			return (ft_clear_memory(shell), NULL);
		shell->export = ft_set_env(envp);
		if (shell->export == NULL)
			return (ft_clear_memory(shell), NULL);
	}
	return (shell);
}
