/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateon <mateon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 01:29:14 by matnusko          #+#    #+#             */
/*   Updated: 2025/09/19 08:07:53 by mateon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putptr(unsigned long long ptr);
int		ft_putnbr(int n);
int		ft_putunsigned(unsigned int n);
int		ft_puthex(unsigned long long num, int uppercase);
int		ft_putpointer(void *ptr);
int		ft_format(const char *str, va_list args);
int		ft_printf(const char *str, ...);
int		ft_putunbr(unsigned int n);

#endif
