/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   buffer_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 12:19:49 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/30 19:32:07 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "ft_printf.h"

t_buff	*new_buff()
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
	return (buffer);
}

void	free_buff(t_buff *buffer)
{
	free(buffer->buff);
	free(buffer->value);
	free(buffer);
}
