/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:42:26 by rothiery          #+#    #+#             */
/*   Updated: 2024/05/16 12:31:00 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

unsigned int	ft_putunl(unsigned long n);
int				ft_printf(const char *str, ...);
unsigned int	ft_putchr(unsigned int c);
unsigned int	ft_putstr(char unsigned *c);
unsigned int	ft_putptr(size_t *c);
unsigned int	ft_putnbr(int n);
unsigned int	ft_putuni(unsigned int i);
unsigned int	ft_putlong(long n);
unsigned int	ft_puthex(size_t i);
unsigned int	ft_puthexmaj(size_t i);
size_t			ft_strlen(const unsigned char *s);
unsigned char	*ft_strdup(const unsigned char *s);

#endif
