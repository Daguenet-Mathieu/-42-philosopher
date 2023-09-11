NAME = philo/philo
NAMEBONUS = philo/philo_bonus


HEADER = philo/philo.h

SRCS = philo/main.c\
	philo/atoi.c\
	philo/destroy.c\
	philo/get_time.c\
	philo/init.c\
	philo/mutex.c\
	philo/monitoring.c\
	philo/print.c\
	philo/routine.c\


OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

CC = cc

FLAGS = -Wall -Werror -Wextra -g

$(NAME) : $(OBJS) $(HEADER)
		 $(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) -MMD -c $< -o $@

all : $(NAME)

clean :
		rm -f $(OBJS) $(DEPS)

fclean : clean
		rm -f $(NAME) $(DEPS)

re : fclean all

-include : $(DEPS)

.PHONY: all clean fclean re
