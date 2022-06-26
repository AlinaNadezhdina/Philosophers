NAME			=	philo

SRCS			=	philo.c\
					ft_atoi.c\
					food_death_monitor.c\
					free_and_destroy.c\
					utils.c\
					detect_errors.c\
					init.c\
					fork_functions.c

SRCS_DIR		=	philo

SOURCES			=	$(addprefix $(SRCS_DIR)/, $(SRCS))

HEADER			=	$(SRCS_DIR)/philo.h

OBJS			=	$(SOURCES:$(SRCS_DIR)/%.c=%.o)

CC				=	cc

RM				=	rm -f

CFLAGS			=	-Wextra -Werror -Wall  -fsanitize=thread -g

.PHONY			:	all clean fclean re bonus

all				:	$(NAME)

$(NAME)			:	$(OBJS)
	$(CC) $(CFLAGS)  $^ -o $(NAME)


%.o				:	$(SRCS_DIR)/%.c $(HEADER)
	 $(CC) $(CFLAGS) -c $< -o $@

clean			:	
	$(RM) $(OBJS)


fclean			:	clean
	$(RM)  $(NAME)

re				: fclean all