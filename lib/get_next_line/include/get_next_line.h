/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:22:52 by jgossard          #+#    #+#             */
/*   Updated: 2025/03/17 14:08:36 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include "stdlib.h" // malloc, free, NULL
# include "unistd.h" // read
# include <stdio.h> // printf

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# define MAX_FD_OPENED 1024

char	*get_next_line(int fd);
int		get_line_info(t_list **buffer, int *line_len);
#endif
