# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/16 13:47:55 by bkwag             #+#    #+#              #
#    Updated: 2021/06/16 15:58:19 by bkwag            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= main.c utils.c init.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.
LIBS			= -lpthread

NAME			= philo

all:			$(NAME)

$(NAME):		$(OBJS)
				@gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				@$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
