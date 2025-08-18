/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_list_open_fds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 11:36:43 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/14 12:25:47 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

// void	ft_debug_list_open_fds(const char *tag)
// {
// 	DIR *d = opendir("/proc/self/fd");
// 	if (!d)
// 	{
// 		perror("opendir");
// 		return;
// 	}
// 	struct dirent *de;
// 	dprintf(STDERR_FILENO, "FDs @ %s:\n", tag);
// 	while ((de = readdir(d))) {
// 		if (de->d_name[0] == '.') continue;
// 		dprintf(STDERR_FILENO, "  fd=%s\n", de->d_name);
// 	}
// 	closedir(d);
// }

// TODO: delete this file


void	ft_debug_list_open_fds(const char *label)
{
	DIR *d = opendir("/proc/self/fd");
	if (!d) {
		perror("opendir");
		return;
	}

	struct dirent *entry;
	char path[256];
	char target[256];
	ssize_t len;

	fprintf(stderr, "FDs @ %s:\n", label);
	while ((entry = readdir(d))) {
		if (entry->d_name[0] == '.')
			continue;

		snprintf(path, sizeof(path), "/proc/self/fd/%s", entry->d_name);
		len = readlink(path, target, sizeof(target) - 1);
		if (len != -1) {
			target[len] = '\0';
			fprintf(stderr, "  fd=%s -> %s\n", entry->d_name, target);
		}
	}
	closedir(d);
}
