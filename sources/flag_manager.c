/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flag_manager.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 12:49:17 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/30 18:42:31 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag	*new_flag(char flag)
{
	t_flag	*new;

	if (!(new = (t_flag *)malloc(sizeof(t_flag))))
		return (NULL);
	new->flag = flag;
	new->next = NULL;
	return (new);
}

void	free_flag(t_flag *f)
{
	free(f);
	f = NULL;
}

void 	free_flags(t_arg *arg)
{
	t_flag	*to_free;
	t_flag	*current;

	current = arg->flag;
	while (current)
	{
		to_free = current;
		free(to_free);
		to_free = NULL;
		current = current->next;
	}
}

int		flag(t_arg *arg, char flag)
{
	t_flag	*current;

	if (!(arg->flag))
		return (0);
	current = arg->flag;
	while (current)
	{
		if (current->flag == flag)
			return (1);
		current = current->next;
	}
	return (0);
}

int		add_flag(t_arg *arg, char f)
{
	t_flag	*new;

	if (!(new = new_flag(f)))
		return (0);
	new->next = arg->flag;
	arg->flag = new;
	return (1);
}
