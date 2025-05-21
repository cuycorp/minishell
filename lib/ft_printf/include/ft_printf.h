/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:52:19 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/06 21:04:28 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include "ft_utils.h"

// Macros Object
# define BASE_10 10
# define BASE_16 16
# define DECIMAL_DIGITS "0123456789"
# define LOWER_HEXA_DIGITS "0123456789abcdef"
# define UPPER_HEXA_DIGITS "0123456789ABCDEF"

//	Structure
typedef struct s_flags
{
	int	minus;
	int	zero;
	int	period;
	int	precision;
	int	hashtag;
	int	space;
	int	plus;
	int	star;
	int	width;
	int	fd;
}	t_flags;

// Functions
int		ft_printf(int fd, const char *str, ...);

// Parsers Functions
int		ft_parse(const char *str, va_list *args_list, int *index, int fd);
int		ft_parse_flags(char c, t_flags *flags, va_list *args_list);
int		ft_parse_specifier(char c, va_list *args_list, t_flags *flags);

// Formatters Functions
int		ft_format_char_with_flags(char c, t_flags *flags);
int		format_string_with_padding(char *str, int precision_len, \
		int padding, t_flags *flags);
int		handle_sign_and_pad(int sign, int numlen, int pad, t_flags *f);
int		format_number(long int number, int base, char *base_chars, \
		t_flags *flags);
int		format_unumber(unsigned int number, int base, char *base_chars, \
		t_flags *flags);
int		ft_format_pointer_address(void *memory_address, t_flags *flags);

// Printers Functions
int		ft_print_char_with_flags(char c, t_flags *flags);
int		ft_print_string_with_flags(char *str, t_flags *flags);
int		ft_print_nbr(long int number, int base, char *base_chars, \
		t_flags *flags);
int		ft_print_unbr(unsigned int number, int base, char *base_chars, \
		t_flags *flags);
int		ft_print_pointers(void *memory_address, t_flags *flags);
#endif
