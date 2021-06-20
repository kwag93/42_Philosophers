# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/16 13:47:55 by bkwag             #+#    #+#              #
#    Updated: 2021/06/20 11:54:58 by bkwag            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= main.c utils.c utils2.c init.c message.c eat.c forks.c exit.c monitor.c sem.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.
LIBS			= -lpthread

NAME			= philo_bonus

all:			$(NAME)

$(NAME):		$(OBJS)
				@gcc ${CFLAGS} -g -o ${NAME} ${OBJS} ${LIBS}

clean:
				@$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
