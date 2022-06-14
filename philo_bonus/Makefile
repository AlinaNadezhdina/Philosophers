NAME			=	philo_bonus

SRCS			=	philo_bonus.c\
					ft_atoi_bonus.c\
					parse_args_bonus.c\
					init_types_bonus.c

SRCS_DIR		=	philo_bonus

SOURCES			=	$(addprefix $(SRCS_DIR)/, $(SRCS))

HEADER			=	$(SRCS_DIR)/philo.h

# OBJ_PATH		=	obj

OBJS			=	$(SOURCES:$(SRCS_DIR)/%.c=%.o)

CC				=	gcc

RM				=	rm -f

CFLAGS			=	-Wextra -Werror -Wall #-fsanitize=thread -g

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