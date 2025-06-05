/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:28:04 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:47:49 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_reset_shell(t_shell *data)
{
	if (!data)
		return ;
	if (data->input)
		free(data->input);
	if (data->tokens_list)
		ft_free_tokens_list(&data->tokens_list);
}

static char	*ft_set_prompt(t_shell *data)
{
	char	*prompt;
	int		i;
	char	*pwd;

	i = 0;
	while (data->ev[i] && ft_strncmp(data->ev[i], "PWD", ft_strlen("PWD")) != 0)
		i++;
	pwd = &data->ev[i][18];
	prompt = ft_strjoin(pwd, " Oh-My-Shell > ");
	return (prompt);
}

void	ft_handle_shell(t_shell *data)
{
	int	i;

	i = 0;
	while (1)
	{
		data->input = readline(ft_set_prompt(data)); // make prompt a variable
		if (!data->input)
			return (ft_close_program(data, EXIT_FAILURE));
		if (*data->input == '\0')
			continue ;
		ft_tokenizer(data->input, data);
		if (!ft_parser(data->tokens_list))
			ft_printf(STDERR_FILENO, "Error: ft_parser failed\n");
		else
			ft_printf(STDIN_FILENO, "Success: ft_parser succeeded\n");

		ft_handle_history(data->input);
		if (ft_strncmp(data->input, EXIT, ft_strlen(EXIT) + 1) == 0)
		{
			ft_putstr_fd(data->input, STDOUT_FILENO);
			break ;
		}
		else
			ft_printf(STDOUT_FILENO, "%s\n", data->input);
		ft_reset_shell(data);
	}
}
