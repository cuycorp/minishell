/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:24:47 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/03 09:55:25 by jgossard         ###   ########.fr       */
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

/* Utils */

bool	ft_is_unquoted_char(char c);
bool	ft_is_double_quoted_char(char c);
bool	ft_is_special_operator(char c);

#endif
