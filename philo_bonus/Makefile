NAME= philo_bonus

SRCS= philo_bonus.c utils_bonus.c utils1_bonus.c utils2_bonus.c init_bonus.c start_bonus.c routine_utils_bonus.c time_bonus.c

OBJS= $(SRCS:.c=.o)

HEADER= philo_bonus.h

CC = cc

CFLAGS= -Wall -Wextra -Werror

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

