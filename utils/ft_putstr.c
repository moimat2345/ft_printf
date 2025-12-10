/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnusko <matnusko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 04:18:33 by mateon            #+#    #+#             */
/*   Updated: 2025/09/08 02:09:07 by matnusko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putstr(char *s)
{
	int	printed;

	printed = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (*s)
	{
		printed += ft_putchar(*s);
		s++;
	}
	return (printed);
}
