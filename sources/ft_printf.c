/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 11:54:50 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/06 13:49:33 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static int		main_buffer(char *format, va_list params)
{
	int		i;
	int		printed;
	t_buff	*p_buff;

	i = 0;
	printed = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (!(p_buff = percent_buffer(format + i, params)))
				return (printed);
			write(1, p_buff->buff, p_buff->buff_size);
			printed += p_buff->buff_size;
			i += p_buff->arg_offset;
			free_buff(p_buff);
		}
		else
		{
			ft_putchar(format[i]);
			printed += 1;
		}
		i++;
	}
	return (printed);
}

int				ft_printf(const char *restrict format, ...)
{
	va_list		params;
	int			printed;
	char		*f;

	f = (char *)format;
	va_start(params, format);
	printed = main_buffer(f, params);
	va_end(params);
	return (printed);
}
