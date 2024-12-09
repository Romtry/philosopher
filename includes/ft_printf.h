/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:42:26 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/09 15:19:52 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_buffer
{
	unsigned char	save[BUFFER_SIZE];
	unsigned int	index;
}	t_buffer;

void			buffer_hit(t_buffer *buffer);
unsigned int	ft_putunl(unsigned long n, t_buffer *buffer);
int				ft_printf(const char *str, ...);
unsigned int	ft_putchr(unsigned int c, t_buffer *buffer);
unsigned int	ft_putstr(char unsigned *c, t_buffer *buffer);
unsigned int	ft_putptr(size_t *c, t_buffer *buffer);
unsigned int	ft_putnbr(int n, t_buffer *buffer);
unsigned int	ft_putuni(unsigned int i, t_buffer *buffer);
unsigned int	ft_putlong(long n, t_buffer *buffer);
unsigned int	ft_puthex(size_t i, t_buffer *buffer);
unsigned int	ft_puthexmaj(size_t i, t_buffer *buffer);
size_t			ft_strlen(const unsigned char *s);

#endif
