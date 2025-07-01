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

static bool	ft_save_wd(char *variable)
{
	if (!getcwd(variable, PATH_MAX))
	{
		return (false);
	}
	return (true);
}

static bool	ft_update_path(t_command command, char *old_pwd, char *pwd)
{
	ft_save_wd(old_pwd);
	if (chdir(command.args[0]))
	{
		perror("cd");
		ft_printf(STDOUT_FILENO, ": %s\n", command.args[0]);
		return (false);
	}
	ft_save_wd(pwd);
	return (true);
}

static void	ft_realloc_env_variable(t_shell **data, char *srch, char *env_var)
{
	int	i;

	i = 0;
	while ((*data)->ev[i] && ft_strncmp((*data)->ev[i], srch, ft_strlen(srch)) != 0)
		i++;
	free((*data)->ev[i]);
	(*data)->ev[i] = ft_strjoin(srch, env_var);
}

static void	ft_update_env_variables(t_shell **data, char *old_pwd, char *pwd)
{
	ft_realloc_env_variable(data, "PWD=", pwd);
	ft_realloc_env_variable(data, "OLDPWD=", old_pwd);
}

int	function_cd(t_shell **data, t_command command)
{
	char	old_pwd[PATH_MAX];
	char	pwd[PATH_MAX];
	// int		i;

	// i = 0;
	if (!ft_update_path(command, old_pwd, pwd))
		return (1);
	ft_update_env_variables(data, old_pwd, pwd);
	return (0);
}

/*
printf("variables temporales\nOLD_PWD %s\nPWD %s\n", old_pwd, pwd);
printf("printing copy of env\n");
while (i < 52)
{
	printf("%s\n", data->ev[i]);
	i++;
}
*/
