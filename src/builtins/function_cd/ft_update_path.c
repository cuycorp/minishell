/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:09:21 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/24 09:25:47 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_save_wd(char *variable)
{
	if (!getcwd(variable, PATH_MAX))
		return (false);
	return (true);
}


bool	ft_update_path(t_command *command, char *old_pwd, char *pwd,
							char *in_chdir)
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
		ft_printf(STDOUT_FILENO, ": %s\n", command->args[0]); // TODO: should be STDERRO_FILENO instead of STDOUT_FILENO
		return (free(in_chdir), false);
	}
	if (!ft_save_wd(pwd))
		return (free(in_chdir), false);
	return (free(in_chdir), true);
}
