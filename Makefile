# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matnusko <matnusko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 19:09:35 by matnusko          #+#    #+#              #
#    Updated: 2025/09/08 02:05:14 by matnusko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

FLAG = -Wall -Wextra -Werror

SRCS =	ft_printf.c \
		utils/ft_putchar.c \
		utils/ft_puthex.c \
		utils/ft_putnbr.c \
		utils/ft_putpointer.c \
		utils/ft_putstr.c \
		utils/ft_putunsigned.c \
		utils/ft_putunbr.c

NAMELIB = libftprintf.a

OBJ = ${SRCS:.c=.o}

INCLUDE = ft_printf.h

.c.o:
			${CC} ${FLAG} -I ${INCLUDE} -c $< -o $@
			
all:		${NAMELIB}

${NAMELIB}:		${OBJ}
	ar rcs ${NAMELIB} ${OBJ}
	
clean:
	rm -f ${OBJ}
	
fclean: clean
	rm -f ${NAMELIB}
	
re:	fclean all
	
.PHONY:		all clear fclean re 
		
