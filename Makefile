CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
RM 				= rm -f
HEADERS 		= -I./includes
LIBS 			= -Llibft -lft
LIBFT 			= libft/libft.a
SHARED_SRCS		= shared/utils.c \
				  shared/parse_arguments.c
SHARED_OBJS 	= $(SHARED_SRCS:.c=.o)
CHECKER 		= checker
CHECKER_SRCS	= the_checker/main.c \
				  the_checker/stacks.c \
				  the_checker/statements.c \
				  the_checker/get_next_line_utils.c \
				  the_checker/get_next_line.c
CHECKER_OBJS 	= $(CHECKER_SRCS:.c=.o)
SOLVER 			= push_swap
SOLVER_SRCS		= 
SOLVER_OBJS 	= $(SOLVER_SRCS:.c=.o)

all: $(CHECKER) $(SOLVER)

.c.o:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(CHECKER): $(SHARED_OBJS) $(CHECKER_OBJS) $(LIBFT)
	$(CC) $(SHARED_OBJS) $(CHECKER_OBJS) $(LIBS) -o $(CHECKER)

$(SOLVER): $(SHARED_OBJS) $(SOLVER_OBJS) $(LIBFT)
	$(CC) $(SHARED_OBJS) $(SOLVER_OBJS) $(LIBS) -o $(SOLVER)

$(LIBFT):
	@$(MAKE) bonus -C libft

clean:
	$(RM) $(CHECKER_OBJS)
	$(RM) $(SOLVER_OBJS)
	@$(MAKE) clean -C libft

fclean: clean
	$(RM) $(CHECKER)
	$(RM) $(SOLVER)
	$(RM) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
