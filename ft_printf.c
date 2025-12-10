/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnusko <matnusko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 20:46:48 by matnusko          #+#    #+#             */
/*   Updated: 2025/10/19 00:01:17 by matnusko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(const char *str, va_list args)
{
	if (str[1] == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (str[1] == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (str[1] == 'p')
		return (ft_putpointer(va_arg(args, void *)));
	else if (str[1] == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (str[1] == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (str[1] == 'u')
		return (ft_putunbr(va_arg(args, int unsigned)));
	else if (str[1] == 'x')
		return (ft_puthex((unsigned int)va_arg(args, unsigned int), 0));
	else if (str[1] == 'X')
		return (ft_puthex((unsigned int)va_arg(args, unsigned int), 1));
	else if (str[1] == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		printed;
	va_list	args;

	if (!str)
		return (-1);
	i = 0;
	printed = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && (str[i + 1] == 'c' || str[i + 1] == 's'
				|| str[i + 1] == 'p' || str[i + 1] == 'd'
				|| str[i + 1] == 'i' || str[i + 1] == 'u'
				|| str[i + 1] == 'x' || str[i + 1] == 'X'
				|| str[i + 1] == '%'))
			printed += ft_format(&str[i++], args);
		else
			printed += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (printed);
}

