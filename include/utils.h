/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:24:47 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/16 17:30:59 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structures.h"

/* Validation */
void	ft_validate_args(int argc, t_shell *data);

/* Memory */

void	ft_clear_memory(t_shell *data);
void	ft_close_program(t_shell *data, int exit_code);

/* Parser */

void	ft_advance_token(t_token **token_list);
bool	ft_parse_error(const char *msg);
bool	ft_match_token(t_token **token_list, t_token_type expected);
char	*ft_stringify_token_type(t_token_type type);

/* Utils */

bool	ft_is_unquoted_char(char c);
bool	ft_is_double_quoted_char(char c);
bool	ft_is_special_operator(char c);

bool	ft_is_redirection_type(t_token_type type);
bool	ft_is_word_like_type(t_token_type type);
bool	ft_is_argument_type(t_token_type type);
bool	ft_is_command_terminator(t_token_type type);
bool	ft_is_end_of_command(t_token **token_list);
bool	ft_is_logical_operator(t_token_type type);
#endif
