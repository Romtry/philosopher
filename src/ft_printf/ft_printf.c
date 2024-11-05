/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 08:46:50 by rothiery          #+#    #+#             */
/*   Updated: 2024/05/16 12:19:45 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	cmd(const char *str, va_list args)
{
	if (str[1] == 'c')
		return (ft_putchr(va_arg(args, unsigned int)));
	else if (str[1] == 's')
		return (ft_putstr(va_arg(args, unsigned char *)));
	else if (str[1] == 'p')
		return (ft_putptr(va_arg(args, size_t *)));
	else if (str[1] == 'd' || str[1] == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (str[1] == 'u')
		return (ft_putuni(va_arg(args, unsigned int)));
	else if (str[1] == 'x')
		return (ft_puthex(va_arg(args, unsigned int)));
	else if (str[1] == 'X')
		return (ft_puthexmaj(va_arg(args, unsigned int)));
	else if (str[1] == 'l' && str[2] && str[2] == 'd')
		return (ft_putlong(va_arg(args, long)));
	else if (str[1] == 'l' && str[2] && str[2] == 'u')
		return (ft_putunl(va_arg(args, unsigned long)));
	else if (str[1] == '%')
		return (ft_putchr('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list				args;
	unsigned int		i;
	unsigned int		l;

	i = 0;
	l = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			l += cmd(str + i, args);
			if (str[i + 1])
				i++;
			if (str[i + 1] && ((str[i] == 'l' && str[i + 1] == 'u')
				|| (str[i == 'l'] && str[i + 1] == 'd')))
				i++;
		}
		else
			l += ft_putchr(str[i]);
		i++;
	}
	va_end(args);
	return (l);
}
