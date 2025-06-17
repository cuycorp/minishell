/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:11:13 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/25 19:07:51 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_realloc_env_variable(t_shell **data, char *srch, char *env_var)
{
	int		i;
	char	*new_entry;

	if (!*data || !srch || !env_var)
		return (false);
	i = 0;
	while ((*data)->ev[i])
	{
		if (ft_strncmp((*data)->ev[i], srch, ft_strlen(srch)) == 0)
		{
			new_entry = ft_strjoin(srch, env_var);
			if (!new_entry)
				return (false);
			free((*data)->ev[i]);
			(*data)->ev[i] = new_entry;
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	ft_update_env_variables(t_shell **data, char *old_pwd, char *pwd)
{
	if (!*data || !old_pwd || !pwd)
		return (false);
	if (!ft_realloc_env_variable(data, "PWD=", pwd))
		return (false);
	if (!ft_realloc_env_variable(data, "OLDPWD=", old_pwd))
		return (false);
	return (true);
}

int	function_cd(t_shell **data, t_command *command)
{
	char	old_pwd[PATH_MAX];
	char	pwd[PATH_MAX];
	int		len;
	char	*new_dir;

	if (!*data || !command->args[0] || !command->name || !(*data)->ev)
		return (EXIT_FAILURE);
	len = ft_len_table(command->args);
	if (ft_validate_command(command, "cd") == false)
		return (EXIT_FAILURE);
	if (len == 1 || len == 2)
	{
		new_dir = get_new_dir(len, *data, command);
		if (!new_dir)
			return (EXIT_FAILURE);
		if (!ft_update_path(command, old_pwd, pwd, new_dir))
			return (EXIT_FAILURE);
		if (!ft_update_env_variables(data, old_pwd, pwd))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else
		return (perror("cd: string not in pwd"), EXIT_FAILURE);
}
/*
	printf("variables temporales\nOLD_PWD %s\nPWD %s\n", old_pwd, pwd);
*/
