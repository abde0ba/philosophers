# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darkab <darkab@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 22:06:46 by abbaraka          #+#    #+#              #
#    Updated: 2024/04/20 13:30:33 by darkab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

SRCS= philo.c utils.c utils1.c utils2.c philo_utils.c time.c

OBJS= $(SRCS:.c=.o)

HEADER= philo.h

CC = cc

CFLAGS= -Wall -Wextra -Werror -fsanitize=thread

RM= rm -rf

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean : 
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

