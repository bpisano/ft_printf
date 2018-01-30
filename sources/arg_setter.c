/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arg_setter.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 13:58:46 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/30 18:16:53 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void		set_flag(t_arg **arg, char f, int *i, int *part)
{
	add_flag(*arg, f);
	*i += 1;
	*part = 1;
}

static void		set_f_width(t_arg **arg, char *format, int *i, int *part)
{
	int		j;

	j = 0;
	while (ft_isdigit(format[j]))
	{
		(*arg)->f_width = (*arg)->f_width * 10 + format[j] - 48;
		j++;
	}
	*i += j;
	*part = 2;
}

static void		set_precision(t_arg **arg, char *format, int *i, int *part)
{
	int		j;

	j = 0;
	(*arg)->prec = 0;
	while (ft_isdigit(format[j]))
	{
		(*arg)->prec = (*arg)->prec * 10 + format[j] - 48;
		j++;
	}
	*i += j + 1;
	*part = 3;
}

static void		set_modifier(t_arg **arg, char *format, int *i, int *part)
{
	int		j;
	int		mod;

	j = 0;
	mod = 0;
	while (is_modifier(format[j]))
	{
		if (mod < 2)
			mod++;
		j++;
	}
	(*arg)->modifier = ft_strsub(format, 0, mod);
	*i += j;
	*part = 4;
}

t_arg	*get_arg(char *format, va_list params)
{
	int		i;
	int		part;
	t_arg	*arg;

	if (!(arg = new_arg()))
		return (NULL);
	i = 1;
	part = 0;
	while (!is_type(format[i]) && format[i])
	{
		if (is_flag(format[i]) && part <= 1)
			set_flag(&arg, format[i], &i, &part);
		else if (ft_isdigit(format[i]) && part < 2)
			set_f_width(&arg, format + i, &i, &part);
		else if (format[i] == '.' && part < 3)
			set_precision(&arg, format + i + 1, &i, &part);
		else if (is_modifier(format[i]) && part <= 4)
			set_modifier(&arg, format + i, &i, &part);
		else
			return (NULL);
	}
	if (!format[i])
		return (NULL);
	arg->type = format[i];
	set_arg_value(&arg, params);
	return (arg);
}
