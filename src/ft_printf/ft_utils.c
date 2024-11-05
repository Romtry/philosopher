/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:06:35 by rothiery          #+#    #+#             */
/*   Updated: 2024/05/14 11:20:04 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_putstr(unsigned char *c)
{
	int	i;

	i = 0;
	if (!c)
		c = (unsigned char *)"(null)";
	while (c[i])
	{
		write(1, &c[i], 1);
		i++;
	}
	return (i);
}

unsigned int	ft_putchr(unsigned int c)
{
	write(1, &c, 1);
	return (1);
}

unsigned char	*ft_strdup(const unsigned char *s)
{
	unsigned char	*str;
	unsigned int	i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (i - 1 != (unsigned int)ft_strlen(s))
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

size_t	ft_strlen(const unsigned char *s)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
