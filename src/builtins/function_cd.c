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

/*
	Ongoing : check case for no args
	Todo : remove ft_expand_var, implemented in expansion_n_removal branch
*/

static bool	ft_save_wd(char *variable)
{
	if (!getcwd(variable, PATH_MAX))
		return (false);
	return (true);
}

static char	*ft_find_env_value(char *full_var, char **env) // removed
{
	int i;
	int len;
	char *expanded_value;

	if (!full_var || !env)
		return (NULL);
	len = ft_strlen(full_var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], full_var, len) == 0)
		{
			expanded_value = ft_strdup(&env[i][len]);
			if (!expanded_value)
				return (NULL);
			return (expanded_value);
		}
		i++;
	}
	return (NULL);
}

static char	*ft_local_expand_var(char *var_name, t_shell *data) // removed
{
	char *full_var;
	char *expanded_value;

	if (!var_name || !data || !data->ev)
		return (NULL);
	full_var = ft_strjoin(var_name, "=");
	if (!full_var)
		return (NULL);
	expanded_value = ft_find_env_value(full_var, data->ev);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	free(full_var);
	return (expanded_value);
}

char	*ft_get_home_path(t_shell *data)
{
	char	*home_path;

	if (!data)
		return (NULL);
	home_path = ft_local_expand_var("HOME", data);
	if (!home_path)
		return (NULL);
	return (home_path);
}

static bool	ft_update_path(t_command *command, char *old_pwd, char *pwd, char *in_chdir) // EDITING
{
	if (!command || !old_pwd || !pwd || !in_chdir)
		return (false);
	if (ft_strlen(in_chdir) == 0)
		return (perror("cd: HOME not set"), false);
	if (!ft_save_wd(old_pwd))
		return (free(in_chdir), false);
	if (chdir(in_chdir) != 0)
	{
		perror("cd");
		ft_printf(STDOUT_FILENO, ": %s\n", command->args[0]);
		return (free(in_chdir), false);
	}
	if (!ft_save_wd(pwd))
		return (free(in_chdir), false);
	return (free(in_chdir), true);
}

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

static char	*get_new_dir(int len, t_shell *data, t_command *command)
{
	char	*new_dir;

	if (len == 1)
		new_dir = ft_get_home_path(data);
	else
		new_dir = ft_strdup(command->args[1]);
	if (!new_dir)
		return (NULL);
	return (new_dir);
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
		printf("variables temporales\nOLD_PWD %s\nPWD %s\n", old_pwd, pwd);
			/// removed
		return (EXIT_SUCCESS);
	}
	else
		return (perror("cd: string not in pwd"), EXIT_FAILURE);
}
