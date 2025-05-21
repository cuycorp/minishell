/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:15:08 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/12 13:43:23 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

typedef struct s_flags	t_flags;

// Flag Setters
t_flags	ft_initialise_flags(void);
void	ft_set_flag_period(t_flags *flags);
void	ft_set_flag_star(t_flags *flags, va_list *args_list);
void	ft_set_digits(char c, t_flags *flags);
void	ft_set_flag_minus(t_flags *flags);

// Flag Getters
int		ft_isspecifier(char c);
int		ft_isflags(char c);

// Utility Functions
int		handle_precision(char *str, t_flags *flags);
int		ft_add_padding(char c, int padding, int fd);
int		handle_padding(int len, int total_len);
int		handle_sign(int sign, t_flags *flags);
int		handle_special_case(long int number, t_flags *flags);
int		set_sign_minus(int sign, int fd);
int		ft_handle_hash(unsigned int number, t_flags *f, int base,
			char *base_chars);
int		ft_number_length(long number, int base);
int		ft_putchar(int c, int fd);
int		ft_putstr(const char *str, int fd);
int		ft_putnstr(const char *str, int n, int fd);
int		ft_putnbr(long int number, int number_base, char *base_chars, \
		t_flags *flags);
int		ft_putunbr(unsigned long int number, int number_base, \
		char *base_chars, t_flags *flags);

#endif
