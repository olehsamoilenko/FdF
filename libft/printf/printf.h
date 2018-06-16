/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:06:06 by osamoile          #+#    #+#             */
/*   Updated: 2018/05/01 14:06:10 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# define NONE 0
# define HH 1
# define H 2
# define Z 3
# define L 4
# define LL 5
# define J 6
# define _7BITS 127
# define _8BITS 255
# define _11BITS 2047
# define _16BITS 65535
# define _00000111 7
# define _00001111 15
# define _00011111 31
# define _00111111 63
# define _10000000 128
# define _11000000 192
# define _11100000 224
# define _11110000 240
# include <stdarg.h>

typedef struct	s_pattern
{
	int			hash;
	int			minus;
	int			plus;
	int			space;
	int			zero;
	int			width;
	int			precision;
	int			cast;
	char		type;
}				t_pattern;

typedef struct	s_spaces
{
	int			start;
	int			end;
	int			zeroes;
	char		*prefix;
}				t_spaces;

int				ft_printf(const char *format, ...);
int				type_o(va_list argptr, t_pattern tmp);
int				type_hex(va_list argptr, t_pattern tmp);
int				type_integer(va_list argptr, t_pattern tmp);
int				type_s(va_list argptr, t_pattern tmp);
int				print_c(int c, t_pattern tmp);
int				type_c(va_list argptr, t_pattern tmp);
int				type_unsigned(va_list argptr, t_pattern tmp);
void			flags_width_prec_cast(const char *format, int *i,
					t_pattern *tmp);
t_spaces		new_spaces(void);
t_pattern		new_value(void);
int				get_size(int c);
int				is_type(char c);
int				is_cast(char c);
int				is_flag(char c);

#endif
