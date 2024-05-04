SRCS			=	main.c\
					utils.c\
					utils_sequel.c\
					thread.c\

OBJS			=	$(SRCS:.c=.o)

CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror

NAME			=	philo

all:			$(NAME)

$(NAME):		$(OBJS)
				@echo "\nLa compilation est en cours...\n"
				@$(CC) $(CFLAGS) -s $(OBJS) -o $(NAME)
				@echo "La compilation est terminée !\n"

%.o: %.c
				@$(CC) $(CFLAGS) $(INCLUDES) -g3 -I/usr/include -O3 -c $< -o $@

clean:
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)
				@echo "\net fclean\n"

re:				fclean $(NAME)

.PHONY:			all clean fclean re
