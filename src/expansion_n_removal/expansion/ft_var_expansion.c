/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:45:22 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/13 18:45:24 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*ft_expand_var(char *var_name, t_shell *data)
{
	int	i;
	int	len;

	i = 0;
	var_name = ft_strjoin(var_name, "=");
	len = ft_strlen(var_name);
	while (data->ev[i])
	{
		if (data->ev[i] && ft_strncmp(data->ev[i], var_name, len) == 0)
			return (free(var_name), ft_strdup(&data->ev[i][len]));
		i++;
	}
	return (free(var_name), ft_strdup(""));
}

static char	*ft_locate_var(char *str, int *i)
{
	int	start;
	int	length;

	start = 0;
	length = 0;
	while (str[*i])
	{
		if (str[*i] == '$')
		{
			(*i)++;
			start = *i;
			while ((ft_isalnum(str[*i]) || str[*i] == '_') && str[*i])
				(*i)++;
			length = *i - start;
			return (ft_substr(str, start, length));
		}
		else
			(*i)++;
	}
	return (0);
}

static void	ft_append_char(char **dest, char c)
{
	char	*tmp;
	char	*char_str;

	tmp = *dest;
	char_str = ft_char_2_str(c);
	*dest = ft_strjoin(*dest, char_str);
	free(tmp);
	free(char_str);
}
static char	*ft_fill_expanded_variables(char *str, t_shell *data)
{
	int		i;
	char	*var;
	char	*expanded;
	char	*final;
	char	*tmp;

	i = 0;
	final = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
				+ 1] == '_'))
		{
			var = ft_locate_var(str, &i);
			expanded = ft_expand_var(var, data);
			tmp = final;
			final = ft_strjoin(final, expanded);
			free(tmp);
			free(expanded);
			free(var);
		}
		else
			ft_append_char(&final, str[i++]);
	}
	return (free(str), final);
}

int	ft_var_expansion(t_token **token_list, t_shell *data)
{
	t_token	*current;

	current = *token_list;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC && current->next
			&& ft_is_valid_token_heredoc(current->next->type))
			current = current->next->next;
		else
		{
			if (current->type == TOKEN_DOUBLE_QUOTED_WORD
				|| current->type == TOKEN_EXPANSION
				|| current->type == TOKEN_WORD)
				current->value = ft_fill_expanded_variables(current->value,
						data);
			current = current->next;
		}
	}
	return (0);
}
