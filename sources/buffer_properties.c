/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   buffer_properties.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 19:03:21 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/30 19:08:02 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		resize_value(t_buff **buffer, t_arg *arg)
{
	char	*zero;
	char	*join;
	char	*tmp;

	zero = ft_strset('0', arg->prec - ft_strlen((*buffer)->value));
	join = ft_strjoin(zero, (*buffer)->value);
	tmp = (*buffer)->value;
	(*buffer)->value = join;
	free(tmp);
	free(zero);
	free(join);
}

void		set_buff_value(t_buff **buffer, t_arg *arg)
{
	if (num_type(arg) && arg->prec == 0 && arg_v(arg) == 0)
		(*buffer)->value = ft_strnew(0);
	else if (int_type(arg))
		(*buffer)->value = ft_itoa_base_arg(arg_v(arg), 10, arg);
	else if (uint_type(arg))
		(*buffer)->value = ft_uitoa_base_arg(arg_v(arg), 10, arg);
	else if (hex_type(arg) || point_type(arg))
		(*buffer)->value = ft_uitoa_base_arg(arg_v(arg), 16, arg);
	else if (oct_type(arg))
		(*buffer)->value = ft_uitoa_base_arg(arg_v(arg), 8, arg);
	else if (percent_type(arg))
		(*buffer)->value = ft_strdup("%");
	else if (char_type(arg))
		(*buffer)->value = ctos((arg->value)->schar);
	else if (string_type(arg))
	{
		if (arg->prec < (int)ft_strlen((arg->value)->string))
			(*buffer)->value = ft_strsub((arg->value)->string, 0, arg->prec);
		else
			(*buffer)->value = (arg->value)->string;
	}
	if (num_type(arg) && arg->prec > (int)ft_strlen((*buffer)->value))
		resize_value(buffer, arg);
	(*buffer)->v_size = char_type(arg) ? 1 : ft_strlen((*buffer)->value);
}

void		set_buff_sup(t_buff **buffer, t_arg *arg)
{
	if ((hex_type(arg) || point_type(arg)) && flag(arg, '#') && arg_v(arg) != 0)
	{
		(*buffer)->sup_size = 2;
		(*buffer)->sup = arg->type == 'X' ? "0X" : "0x";
	}
	else if (int_type(arg) && (flag(arg, ' ') || flag(arg, '+')))
	{
		(*buffer)->sup_size = 1;
		(*buffer)->sup = arg_v(arg) > 0 ? "+" : "-";
	}
	else if (int_type(arg) && arg_v(arg) < 0)
	{
		(*buffer)->sup_size = 1;
		(*buffer)->sup = "-";
	}
	else if (oct_type(arg) && flag(arg, '#') && arg_v(arg) != 0 && arg->prec != 0)
	{
		(*buffer)->sup_size = 1;
		(*buffer)->sup = "0";
	}
	else
		(*buffer)->sup_size = 0;

}

void		set_buff_size(t_buff **buffer, t_arg *arg)
{
	if ((*buffer)->v_size + (*buffer)->sup_size > arg->f_width)
		(*buffer)->buff_size = (*buffer)->v_size + (*buffer)->sup_size;
	else
		(*buffer)->buff_size = arg->f_width;
}

void		set_buff_sup_pos(t_buff **buffer, t_arg *arg)
{
	int		pos;

	pos = (*buffer)->buff_size - (*buffer)->v_size - (*buffer)->sup_size;
	if (flag(arg, '0') || flag(arg, '-'))
		pos = 0;
	(*buffer)->sup_pos = pos;
}
