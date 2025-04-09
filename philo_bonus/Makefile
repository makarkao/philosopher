SRCS = clean_philo_bonus.c init_philo_bonus.c philo_bonus.c philo_tools_bonus.c death_handler_bonus.c eat_sleep_handler_bonus.c philo_tools_2_bonus.c eat_sleep_tools_bonus.c error_message_bonus.c

OBJS = ${SRCS:.c=.o}

NAME = philo_bonus

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean

.SECONDARY: OBJS