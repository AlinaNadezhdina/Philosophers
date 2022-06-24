NAME			=	philo_bonus

SRCS			=	philo_bonus.c\
					ft_atoi_bonus.c\
					detect_errors_bonus.c\
					init_bonus.c\
					food_life_monitor_bonus.c\
					free_and_destroy_bonus.c\
					utils_bonus.c\
					from_libft_bonus.c

SRCS_DIR		=	philo_bonus

SOURCES			=	$(addprefix $(SRCS_DIR)/, $(SRCS))

HEADER			=	$(SRCS_DIR)/philo_bonus.h

# OBJ_PATH		=	obj

OBJS			=	$(SOURCES:$(SRCS_DIR)/%.c=%.o)

CC				=	gcc

RM				=	rm -f

CFLAGS			=	-Wextra -Werror -Wall -fsanitize=address -g

.PHONY			:	all clean fclean re

all				:	$(NAME)

$(NAME)			:	$(OBJS)
	$(CC) $(CFLAGS)  $^ -o $(NAME)


%.o				:	$(SRCS_DIR)/%.c $(HEADER)
# @mkdir $(OBJ_PATH) 2> /dev/null || true
	 $(CC) $(CFLAGS) -c $< -o $@

clean			:	
	$(RM) $(OBJS)
# $(RM) $(OBJS_B)
# @rmdir  $(OBJ_PATH) 2> /dev/null || true


fclean			:	clean
	$(RM)  $(NAME)

re				: fclean all