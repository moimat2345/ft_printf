/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnusko <matnusko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 04:18:44 by matnusko          #+#    #+#             */
/*   Updated: 2025/09/08 03:10:13 by matnusko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putpointer(void *ptr)
{
	int					printed;

	if (!ptr)
		return (ft_putstr("(nil)"));
	printed = 0;
	printed += ft_putstr("0x");
	printed += ft_puthex((unsigned long long)ptr, 0);
	return (printed);
}
