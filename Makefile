CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
RM 				= rm -f
HEADERS 		= -I./includes
LIBS 			= -Llibft -lft
LIBFT 			= libft/libft.a
CHECKER 		= checker
CHECKER_SRCS	= the_checker/main.c \
				  the_checker/parse_arguments.c \
				  the_checker/stacks.c \
				  the_checker/utils.c \
				  the_checker/statements.c \
				  the_checker/get_next_line_utils.c \
				  the_checker/get_next_line.c
CHECKER_OBJS 	= $(CHECKER_SRCS:.c=.o)
SOLVER 			= push_swap
SOLVER_SRCS		= 
SOLVER_OBJS 	= $(SOLVER_SRCS:.c=.o)

all: $(CHECKER)

.c.o:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(CHECKER): $(CHECKER_OBJS) $(LIBFT)
	$(CC) $(CHECKER_OBJS) $(LIBS) -o $(CHECKER)

$(SOLVER): $(SOLVER_OBJS) $(LIBFT)
	$(CC) $(SOLVER_OBJS) $(LIBS) -o $(SOLVER)

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
