/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:34:42 by osamoile          #+#    #+#             */
/*   Updated: 2018/06/05 16:34:44 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_flag(t_pattern *tmp, char flag)
{
	if (flag == '#')
		tmp->hash = 1;
	else if (flag == '-')
		tmp->minus = 1;
	else if (flag == '+')
		tmp->plus = 1;
	else if (flag == '0')
		tmp->zero = 1;
	else if (flag == ' ')
		tmp->space = 1;
}

static int	collect_num(const char *format, int *i)
{
	int		buf;
	char	*num;
	int		res;

	buf = *i;
	while (ft_isdigit(format[*i]))
		(*i)++;
	num = ft_strsub(format, buf, *i - buf);
	res = ft_atoi(num);
	ft_strdel(&num);
	return (res);
}

static int	take_cast(const char *format, int *i, t_pattern *tmp)
{
	int		res;

	res = tmp->cast;
	if (format[*i] == 'z' && Z > tmp->cast)
		res = Z;
	else if (format[*i] == 'j' && J > tmp->cast)
		res = J;
	else if (format[*i] == 'l' && format[*i + 1] == 'l' && LL > tmp->cast)
		res = LL;
	else if (format[*i] == 'l' && L > tmp->cast)
		res = L;
	else if (format[*i] == 'h' && format[*i + 1] == 'h' && HH > tmp->cast)
		res = HH;
	else if (format[*i] == 'h' && H > tmp->cast)
		res = H;
	(*i)++;
	if (res == HH || res == LL)
		(*i)++;
	return (res);
}

void		flags_width_prec_cast(const char *format, int *i, t_pattern *tmp)
{
	int buf;

	if (is_flag(format[*i]))
		put_flag(tmp, format[(*i)++]);
	if (format[*i] >= '1' && format[*i] <= '9')
		tmp->width = collect_num(format, i);
	if (format[*i] == '.')
	{
		(*i)++;
		buf = collect_num(format, i);
		if (buf != 0)
			tmp->precision = buf;
		else
			tmp->precision = -1;
	}
	if (is_cast(format[*i]))
		tmp->cast = take_cast(format, i, tmp);
}
