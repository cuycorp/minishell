/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:50:19 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/05 16:51:50 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

typedef struct s_signal_child
{
	struct sigaction	sa_ignore;
	struct sigaction	sa_old_int;
	struct sigaction	sa_old_quit;
}						t_signal_child;

void	ft_ctrl_c(void);
void	ft_ctrl_d(t_shell *data);
void	ft_ctrl_slash(void);
void	ft_restore_signal_parent_simple_command(
			t_signal_child *sig, t_shell *data);
void	ft_set_signal_child(bool is_simple_command);
void	ft_set_signal_parent(t_signal_child *sig);
bool	ft_restore_signal_parent_heredoc(t_signal_child *sig, t_shell *data,
			int fd);

void	ft_set_signal_child_heredoc(void);

#endif
