/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_track_open_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 11:30:26 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 15:11:43 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: delete this file

#include <fcntl.h>

void	ft_track_open_fds(int fd)
{
	fprintf(stderr, "[ft_set_cloexec] Called with fd = %d\n", fd);

	if (fd < 0) {
		fprintf(stderr, "[ft_set_cloexec] Invalid fd (%d), exiting.\n", fd);
		return;
	}

	int flags = fcntl(fd, F_GETFD);
	if (flags == -1) {
		perror("[ft_set_cloexec] fcntl(F_GETFD) failed");
		return;
	}

	if (flags & FD_CLOEXEC) {
		fprintf(stderr, "[ft_set_cloexec] FD_CLOEXEC already set on fd %d.\n", fd);
	} else {
		fprintf(stderr, "[ft_set_cloexec] Setting FD_CLOEXEC on fd %d.\n", fd);
	}

	if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1) {
		perror("[ft_set_cloexec] fcntl(F_SETFD) failed");
	} else {
		fprintf(stderr, "[ft_set_cloexec] Successfully set FD_CLOEXEC on fd %d.\n", fd);
	}
}
