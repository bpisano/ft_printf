/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arg_manager.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 12:46:37 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 18:37:20 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "ft_printf.h"

t_arg	*new_arg(void)
{
	t_arg	*new;
	t_value	*new_value;

	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	if (!(new_value = (t_value *)malloc(sizeof(t_value))))
		return (NULL);
	new->value = new_value;
	new->type = '\0';
	new->flag = NULL;
	new->f_width = 0;
	new->prec = -1;
	new->modifier = NULL;
	return (new);
}

void	free_arg(t_arg *arg)
{
	free(arg->value);
	if (arg->modifier)
		free(arg->modifier);
	free_flags(arg);
	free(arg);
	arg = NULL;
}
