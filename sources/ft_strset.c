/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 18:02:39 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/01 18:59:45 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strset(char c, int size)
{
	char	*str;

	if (size < 0)
		return ("");
	if (!(str = ft_strnew(size)))
		return (NULL);
	ft_memset(str, c, size);
	return (str);
}
