SRCS = philo_clean.c philo_death.c philo_est.c philo_init.c philo_tools.c philo.c philo_manage_threads.c philo_mutex_destroy.c philo_error_message.c philo_printer.c

OBJS = ${SRCS:.c=.o}

NAME = philo

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