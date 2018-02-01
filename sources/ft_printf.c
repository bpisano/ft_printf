/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 11:54:50 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/01 14:04:02 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_strmerge(char **s1, int size1, char *s2, int size2)
{
	char	*tmp;
	char	*join;

	if (size1 == 0)
	{
		*s1 = s2;
		return ;
	}
	if (size2 == 0)
		return ;
	join = ft_strnew(size1 + size2);
	ft_memcpy(join, *s1, size1);
	ft_memcpy(join + size1, s2, size2);	
	tmp = *s1;
	*s1 = join;
	free(tmp);
	free(s2);
}

static void		ft_chrmerge(char **str, int str_size, char c)
{
	char	*c_to_s;

	c_to_s = ft_ctos(c);
	ft_strmerge(str, str_size, c_to_s, 1);
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
			ft_strmerge(&buff, *printed, percent_buff->buff, percent_buff->buff_size);
			*printed += percent_buff->buff_size;
			//free_buff(percent_buff);
			i++;
			while (!is_type(format[i]))
				i++;
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
	int i = 1;
	int *j = &i;
	ft_printf("-->%o %.o %#o %#.o<--\n", 0, 0, 0, 0);
	ft_printf("-->%d %.d<--\n", 0, 0);
	printf("-->%o %.o %#o %#.o<--\n", 0, 0, 0, 0);
	printf("-->%d %.d<--\n", 0, 0);
	return (0);
}*/
