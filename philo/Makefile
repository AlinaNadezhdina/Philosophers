NAME			=	philo

SRCS			=	philo.c\
					ft_atoi.c\
					check_life.c\
					free_and_destroy.c\
					utils.c\
					detect_errors.c\
					parse_args.c\
					fill_set.c\
					init_types.c\
					fork_functions.c

SRCS_DIR		=	philo

SOURCES			=	$(addprefix $(SRCS_DIR)/, $(SRCS))

HEADER			=	$(SRCS_DIR)/philo.h

# OBJ_PATH		=	obj

OBJS			=	$(SOURCES:$(SRCS_DIR)/%.c=%.o)

CC				=	gcc

RM				=	rm -f

CFLAGS			=	-Wextra -Werror -Wall  #-fsanitize=thread -g

.PHONY			:	all clean fclean re bonus

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