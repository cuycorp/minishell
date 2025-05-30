/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:24:47 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/30 15:54:33 by jgossard         ###   ########.fr       */
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

int	ft_is_special_char(char c);

#endif
