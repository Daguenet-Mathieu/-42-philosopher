MANDATORY_DIR=philo2/

NAME = philo2/philo
NAMEBONUS = philo/philo_bonus


HEADER = philo2/philo.h

SRCS = main.c\
	atoi.c\
	get_time.c\
	parse_args.c\
	ft_strlen.c\
	create_mutex.c\
	launch_philo.c\
	monitoring.c\
	destroy_philo.c\
	routine.c\
	print.c\
	strcpy.c\

OBJS = $(addprefix $(MANDATORY_DIR), $(SRCS:.c=.o))
DEPS = $(addprefix $(MANDATORY_DIR), $(SRCS:.c=.d))

CC = cc

FLAGS = -Wall -Werror -Wextra -g

$(NAME) : $(OBJS) $(HEADER)
		 $(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(NAMEBONUS) : $(OBJSBONUS) $(HEADERBONUS)
		 $(CC) $(FLAGS) $(OBJSBONUS) -o $(NAMEBONUS)


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
