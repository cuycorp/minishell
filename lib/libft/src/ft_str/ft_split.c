/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:24:23 by jgossard          #+#    #+#             */
/*   Updated: 2025/04/04 10:35:28 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *str, char sep);
static int	ft_word_len(char const *str, char sep);
static char	**ft_free_all(char **strs, int count);

/**
 * @brief	Counts the number of words in the string `str`
 * 			separated by the delimiter `sep`.
 *
 * @param str The string to be scanned.
 * @param sep The delimiter character.
 * @return The number of words in the string.
 */
static int	ft_count_word(char const *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
		{
			count++;
			while (str[i] && str[i] != sep)
				i++;
		}
	}
	return (count);
}

/**
 * @brief	Calculates the length of a word in the string `str`
 * 			up to the delimiter `sep`.
 *
 * @param str The string to be scanned.
 * @param sep The delimiter character.
 * @return The length of the word.
 */
static int	ft_word_len(char const *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

/**
 * @brief Frees the memory allocated for the array of strings.
 *
 * @param result The array of strings to be freed.
 * @param count The number of strings in the array.
 * @return NULL.
 */
static char	**ft_free_all(char **result, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

/**
 * @brief	Allocates and returns an array of strings obtained
 * 			by splitting `str` using the delimiter `sep`.
 *
 * @param str The string to be split.
 * @param sep The delimiter character.
 * @return A pointer to the array of strings, or NULL if the allocation fails.
 */
char	**ft_split(char const *str, char sep)
{
	char	**strs;
	int		word_len;
	int		j;

	strs = (char **)malloc(sizeof(char *) * (ft_count_word(str, sep) + 1));
	if (!str || !strs)
		return (NULL);
	j = 0;
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		if (*str && *str != sep)
		{
			word_len = ft_word_len(str, sep);
			strs[j] = ft_substr(str, 0, word_len);
			if (!strs[j])
				return (ft_free_all(strs, j));
			str += word_len;
			j++;
		}
	}
	strs[j] = NULL;
	return (strs);
}
