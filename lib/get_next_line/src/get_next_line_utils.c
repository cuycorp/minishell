/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:23:18 by jgossard          #+#    #+#             */
/*   Updated: 2025/03/15 13:07:50 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief	Counts the length of the next line in the buffer and checks for
 * 			newline
 *
 * This function iterates through the buffer to determine the length of the
 * next line and checks if a newline character is present in the buffer.
 *
 * @param buffer Pointer to the head of the linked list buffer
 * @param line_len Pointer to store the calculated line length
 * @return int 1 if a newline character is found, 0 otherwise
 */
int	get_line_info(t_list **buffer, int *line_len)
{
	int		i;
	int		has_new_line;
	t_list	*temp;
	char	*content_str;

	if (!buffer || !line_len)
		return (0);
	*line_len = 0;
	has_new_line = 0;
	temp = *buffer;
	while (temp && !has_new_line)
	{
		content_str = (char *)(temp->content);
		i = 0;
		while (content_str[i])
		{
			(*line_len)++;
			has_new_line = (content_str[i] == '\n');
			if (has_new_line)
				break ;
			i++;
		}
		temp = temp->next;
	}
	return (has_new_line);
}
