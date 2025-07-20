/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:24:47 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 20:12:18 by jgossard         ###   ########.fr       */
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
void	ft_free_redirection(t_redirection **redirection);
void	ft_free_command(t_command *command);
void	ft_free_ast_tree(t_ast_node **root);

/* String */

bool	ft_is_unquoted_char(char c);
bool	ft_is_double_quoted_char(char c);
bool	ft_is_special_operator(char c);

/* Token */

char	*ft_stringify_token_type(t_token_type type);
bool	ft_is_redirection_type(t_token_type type);
bool	ft_is_word_like_type(t_token_type type);
bool	ft_is_argument_type(t_token_type type);
bool	ft_is_command_terminator(t_token_type type);
bool	ft_is_logical_operator(t_token_type type);


int	ft_len_table(char **table);
#endif
