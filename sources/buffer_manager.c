/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   buffer_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 12:19:49 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/01 19:32:11 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

t_buff	*new_buff(void)
{
	t_buff	*buffer;

	if (!(buffer = (t_buff *)malloc(sizeof(t_buff))))
		return (NULL);
	buffer->buff = NULL;
	buffer->buff_size = 0;
	buffer->value = NULL;
	buffer->v_size = 0;
	buffer->sup = NULL;
	buffer->sup_size = 0;
	buffer->sup_pos = 0;
	buffer->arg_offset = 0;
	return (buffer);
}

void	free_buff(t_buff *buffer)
{
	if (buffer->buff)
		ft_memdel((void **)&(buffer->buff));
	if (buffer->value)
		ft_memdel((void **)&(buffer->value));
	if (buffer)
		ft_memdel((void **)&(buffer));
}
