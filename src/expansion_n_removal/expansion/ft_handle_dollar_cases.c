/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_dollar_cases.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:15:59 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/05 14:26:12 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*ft_handle_question_expansion(int *i, char *final, t_shell *data)
{
	char	*exp;

	(*i)+=2;
	if (g_exit_code == 130 || g_exit_code == 131)
	{
		data->exit_code = g_exit_code;
		ft_printf(STDOUT_FILENO, "ft_handle_question_expansion: exit code = %d\n", data->exit_code); // TODO: remove this logs
		g_exit_code = -1;
	}
	exp = ft_strdup(ft_itoa(data->exit_code));
	if (!exp)
		return (NULL);
	final = ft_strjoin(final, exp);
	return (free(exp), final);
}

static char	*ft_handle_dollar_variable(char *str, int *i, char *final,
		t_shell *data)
{
	char	*var;
	char	*expanded;
	char	*tmp;

	var = ft_locate_var(str, i);
	if (!var)
		return (free(final), NULL);
	expanded = ft_expand_var(var, data);
	if (!expanded)
		return (free(final), free(var), NULL);
	tmp = final;
	final = ft_strjoin(final, expanded);
	free(tmp);
	free(expanded);
	free(var);
	if (!final)
		return (NULL);
	return (final);
}

char	*ft_handle_dollar_cases(char *str, int *i, char *final, t_shell *data)
{
	if (!str || !i || !final || !data)
		return (free(final), NULL); // TODO: Mr A added these checks, really need to free here?
	if (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
		return (ft_handle_dollar_variable(str, i, final, data));
	else if (str[*i + 1] == '?')
		return (ft_handle_question_expansion(i, final, data));
	else
		return (free(final), NULL);
}
