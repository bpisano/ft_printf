/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   percent_buffer.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 12:15:39 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/01 17:59:15 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "ft_printf.h"

static void		init_buffer(t_buff **buffer, t_arg *arg)
{
	if (flag(arg, '0') && !flag(arg, '-') && arg->prec == -1)
		(*buffer)->buff = ft_strset('0', (*buffer)->buff_size);
	else
		(*buffer)->buff = ft_strset(' ', (*buffer)->buff_size);
}

static void		copy_value(t_buff **buffer, t_arg *arg)
{
	int		b_s;
	int		v_s;
	int		s_s;

	b_s = (*buffer)->buff_size;
	v_s = (*buffer)->v_size;
	s_s = (*buffer)->sup_size;
	if (flag(arg, '-') || b_s < v_s)
		ft_memcpy((*buffer)->buff + s_s, (*buffer)->value, v_s);
	else
		ft_memcpy((*buffer)->buff + b_s - v_s, (*buffer)->value, v_s);
}

static void		copy_sup(t_buff **buffer, t_arg *arg)
{
	int		b_s;
	int		v_s;
	int		s_s;
	int		s_p;

	b_s = (*buffer)->buff_size;
	v_s = (*buffer)->v_size;
	s_s = (*buffer)->sup_size;
	s_p = (*buffer)->sup_pos;
	if (int_type(arg) && flag(arg, ' '))
		ft_memcpy((*buffer)->buff + s_p, " ", s_s);
	if ((hex_type(arg) && flag(arg, '#') && arg_v(arg) != 0) || point_type(arg))
		ft_memcpy((*buffer)->buff + s_p, arg->type == 'X' ? "0X" : "0x", s_s);
	else if (oct_type(arg) && flag(arg, '#'))
		ft_memcpy((*buffer)->buff + s_p, "0", s_s);
	else if (int_type(arg) && flag(arg, '+'))
		ft_memcpy((*buffer)->buff + s_p, arg_v(arg) < 0 ? "-" : "+", s_s);
	else if ((int_type(arg)) && arg_v(arg) < 0)
		ft_memcpy((*buffer)->buff + s_p, "-", s_s);
}

static void		fill_buff(t_buff **buffer, t_arg *arg)
{
	copy_value(buffer, arg);
	copy_sup(buffer, arg);
}

t_buff			*percent_buffer(char *format, va_list params)
{
	t_arg	*arg;
	t_buff	*buffer;

	if (!(arg = get_arg(format, params)))
		return (NULL);
	if (!(buffer = new_buff()))
		return (NULL);
	buffer->arg_offset = arg->offset;
	if (string_type(arg) && !(arg->value)->string && arg->f_width == 0)
	{
		buffer->buff = ft_strdup("(null)");
		buffer->buff_size = 6;
		return (buffer);
	}	
	set_buff_value(&buffer, arg);
	set_buff_sup(&buffer, arg);
	set_buff_size(&buffer, arg);
	set_buff_sup_pos(&buffer, arg);
	init_buffer(&buffer, arg);
	fill_buff(&buffer, arg);
	//printf("value : %s\n", ft_uitoa_base_arg(uarg_v(arg), 10, arg));
	free_arg(arg);
	//printf("value : \0\n", 0/*buffer->value*/);
	//printf("v_size : %d\n", buffer->v_size);
	//printf("buff_size : %d\n", buffer->buff_size);
	//printf("sup : %s\n", buffer->sup);
	//printf("sup_size : %d\n", buffer->sup_size);
	//printf("sup_pos : %d\n", buffer->sup_pos);
	//printf("%s\n", buffer->buff);
	return (buffer);
}
