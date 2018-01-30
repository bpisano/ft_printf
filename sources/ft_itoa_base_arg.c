/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base_arg.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 16:20:23 by bpisano      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/30 16:52:45 by bpisano     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base_arg(long long n, int base, t_arg *arg)
{
	char	*nbr;
	char	*s_base;

	if (!(nbr = (char *)ft_memalloc(sizeof(char))))
		return (NULL);
	s_base = arg->type == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";
	if (n < -9223372036854775807)
		return ("9223372036854775808");
	if (n < 0)
		nbr = ft_itoa_base_arg(-n, base, arg);
	else
		nbr = n < base ? ft_strdup(ft_strsub(s_base, n % base, 1)) :
			ft_strjoin(ft_itoa_base_arg(n / base, base, arg),
					ft_strsub(s_base, n % base, 1));
	return (nbr);
}

char	*ft_uitoa_base_arg(unsigned long long n, unsigned int base, t_arg *arg)
{
	char	*nbr;
	char	*s_base;

	if (!(nbr = (char *)ft_memalloc(sizeof(char))))
		return (NULL);
	s_base = arg->type == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";	
	nbr = n < base ? ft_strdup(ft_strsub(s_base, n % base, 1)) :
		ft_strjoin(ft_itoa_base_arg(n / base, base, arg),
				ft_strsub(s_base, n % base, 1));
	return (nbr);
}

