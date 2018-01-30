/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 11:54:50 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/30 19:41:13 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void		join_char(char **buff, char c)
{
	char	*tmp;
	char	*c_to_s;

	tmp = *buff;
	c_to_s = ctos(c);
	*buff = ft_strjoin(*buff, c_to_s);
	free(tmp);
	free(c_to_s);
}

static void		join_string(char **s1, char *s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = ft_strjoin(*s1, s2);
	free(tmp);
}

static char		*main_buffer(char *format, va_list params, int *printed)
{
	int		i;
	char	*buff;
	t_buff	*percent_buff;

	i = 0;
	buff = ft_strnew(0);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (!(percent_buff = percent_buffer(format + i, params)))
				return (NULL);
			join_string(&buff, percent_buff->buff);
			*printed += percent_buff->buff_size;
			free_buff(percent_buff);
			i++;
			while (!is_type(format[i]))
				i++;
		}
		else
		{
			join_char(&buff, format[i]);
			*printed += 1;
		}
		i++;
	}
	return (buff);
}

int		ft_printf(const char *restrict format, ...)
{
	int			printed;	
	va_list		params;
	char		*f;
	char		*buff;

	printed = 0;
	f = (char *)format;
	va_start(params, format);
	if (!(buff = main_buffer(f, params, &printed)))
		return (-1);
	write(1, buff, printed);
	va_end(params);
	free(buff);
	return (printed);
}
/*
int		main(void)
{
	ft_printf("test %d\n", -42);
	return (0);
}*/