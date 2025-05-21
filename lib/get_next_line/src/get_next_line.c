/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:23:03 by jgossard          #+#    #+#             */
/*   Updated: 2025/03/17 12:09:07 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Adds a new node with a copy of the given string to the end of the list
 *
 * This function duplicates the provided string `str`, creates a new node with
 * the duplicated string, and appends the node to the end of the given list
 * `buffer`.
 * If the string duplication or node creation fails, the function returns 0.
 * If the node is successfully added, it returns 1.
 *
 * @param buffer The list to which the new node will be added.
 * @param str The string to be duplicated and added to the list.
 * @return 1 if the node is added successfully, 0 otherwise.
 */
static int	add_node(t_list **buffer, char *str)
{
	t_list	*new_node;
	char	*copy;

	if (!buffer && !str)
		return (0);
	copy = ft_strdup(str);
	if (!copy)
		return (0);
	new_node = ft_lstnew(copy);
	if (!new_node)
		return (free(copy), 0);
	ft_lstadd_back(buffer, new_node);
	if (*buffer == NULL)
		return (ft_lstdelone(new_node, free), 0);
	return (1);
}

/**
 * @brief Reads data from a file descriptor and appends lines to the buffer.
 *
 * This function reads data from the provided file descriptor `fd` and appends
 * it to the provided buffer list. The function continues reading until a
 * complete line is acquired (based on the definition of `get_line_info`), or an
 * error occurs.
 * It allocates a temporary string buffer for each read operation.
 * If reading fails or no data is available, it will clear the buffer and return
 *
 * @param buffer A pointer to the buffer list where the data will be appended.
 * @param fd The file descriptor from which data will be read.
 */
static void	read_line(t_list **buffer, int fd)
{
	int		bytes_read;
	int		added;
	int		line_len;
	char	*str;

	if (fd < 0 || !buffer)
		return ;
	while (!get_line_info(buffer, &line_len))
	{
		str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!str)
			return ;
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read < 0)
				ft_lstclear(buffer, free);
			return (free(str));
		}
		str[bytes_read] = '\0';
		added = add_node(buffer, str);
		free(str);
		if (!added)
			return ;
	}
}

/**
 * @brief	Extracts a line of specified length from the buffer and updates
 * 			the remainder.
 *
 * This function extracts a line of length `line_len` from the `buffer` and
 * stores it in the provided `line` variable. If a newline character is
 * encountered, the remainder of the line after the newline is stored in `rest`.
 * The function also handles the cleanup of nodes from the list as it processes
 * the buffer.
 *
 * @param buffer	A pointer to the buffer list from which the line will be
 * 					extracted.
 * @param line_len The length of the line to extract.
 * @param line A buffer where the extracted line will be stored.
 * @param rest A pointer to store the remainder of the line after extraction.
 */
static void	extract_line(t_list **buffer, int line_len, char *line, char **rest)
{
	int		i;
	int		j;
	t_list	*next_node;
	char	*content_str;

	j = 0;
	while (*buffer && j < line_len)
	{
		i = 0;
		next_node = (*buffer)->next;
		content_str = (char *)(*buffer)->content;
		while (content_str[i] && j < line_len)
		{
			line[j] = content_str[i];
			if (content_str[i] == '\n' && content_str[i + 1] != '\0')
				*rest = ft_strdup(content_str + i + 1);
			j++;
			if (content_str[i++] == '\n')
				break ;
		}
		ft_lstdelone(*buffer, free);
		*buffer = next_node;
	}
	line[j] = '\0';
}

/**
 * @brief Retrieves the next line from the buffer.
 *
 * This function retrieves the next line from the buffer. The line is
 * dynamically allocated and returned as a string. The buffer is updated to
 * reflect the remaining data after the line extraction. If the buffer is empty
 * or no new line is found, it returns NULL.
 *
 * @param buffer A pointer to the buffer list containing the data.
 * @return The extracted line, or NULL if no line is found.
 */
static char	*ft_get_line(t_list **buffer)
{
	int		line_len;
	char	*line;
	int		has_newline;
	char	*remainder;

	if (!buffer)
		return (NULL);
	has_newline = get_line_info(buffer, &line_len);
	if (line_len == 0 && !has_newline)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (ft_lstclear(buffer, free), NULL);
	remainder = NULL;
	extract_line(buffer, line_len, line, &remainder);
	if (remainder)
	{
		if (!add_node(buffer, remainder))
			return (free(line), free(remainder), NULL);
		free(remainder);
	}
	return (line);
}

/**
 * @brief Retrieves the next line from a file descriptor.
 *
 * This function reads the next line from the file descriptor `fd` and stores it
 * in the `line` variable. It uses a static buffer to hold the contents between
 * function calls. The function handles errors in file reading and clears the
 * buffer after each line is retrieved. The line is dynamically allocated.
 *
 * @param fd The file descriptor from which to read.
 * @param line A pointer to store the retrieved line.
 * @return	The next line read from the file descriptor, or NULL if EOF is
 * 			reached or an error occurs.
 */
char	*get_next_line(int fd)
{
	static t_list	*buffer[MAX_FD_OPENED];
	char			*line;

	if (fd < 0 || fd >= MAX_FD_OPENED || BUFFER_SIZE <= 0)
		return (NULL);
	read_line(&buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = NULL;
	line = ft_get_line(&buffer[fd]);
	if (!line && buffer[fd])
	{
		free(line);
		ft_lstclear(&buffer[fd], free);
	}
	return (line);
}
