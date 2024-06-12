NAME = philo

SRC = main.c parsing.c tools_help.c ft_init.c routine.c run_monitor.c tools_help2.c

OBJ = $(SRC:.c=.o)

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread # -g -fsanitize=thread

all : $(NAME)

%.o: %.c
	$(CC)  $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

re : all clean
