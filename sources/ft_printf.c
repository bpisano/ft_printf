/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 11:54:50 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/06 16:30:42 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_strmerge(char **s1, int size1, char *s2, int size2)
{
	char	*tmp;
	char	*join;

	join = ft_strnew(size1 + size2);
	ft_memcpy(join, *s1, size1);
	ft_memcpy(join + size1, s2, size2);
	tmp = *s1;
	*s1 = join;
	ft_memdel((void **)&tmp);
}

static void		ft_chrmerge(char **s1, int size1, char c)
{
	char	*c_to_s;

	c_to_s = ft_ctos(c);
	ft_strmerge(s1, size1, c_to_s, 1);
	ft_memdel((void **)&c_to_s);
}

static char		*main_buffer(char *format, va_list params, int *printed)
{
	int		i;
	char	*buff;
	t_buff	*p_buff;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (!(p_buff = percent_buffer(format + i, params)))
				return (!buff ? ft_strnew(0) : buff);
			ft_strmerge(&buff, *printed, p_buff->buff, p_buff->buff_size);
			*printed += p_buff->buff_size;
			i += p_buff->arg_offset;
			free_buff(p_buff);
		}
		else
		{
			ft_chrmerge(&buff, *printed, format[i]);
			*printed += 1;
		}
		i++;
	}
	return (buff);
}

int				ft_printf(const char *restrict format, ...)
{
	va_list		params;
	int			printed;
	char		*buff;
	char		*f;

	f = (char *)format;
	va_start(params, format);
	printed = 0;
	buff = main_buffer(f, params, &printed);
	write(1, buff, printed);
	if (buff)
		ft_memdel((void **)&buff);
	va_end(params);
	return (printed);
}
