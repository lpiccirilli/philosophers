SOURCES = main.c\
		utils.c\
		checks.c\
		init.c\
		threads.c\

OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g 

all: philo

philo: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f philo

re: fclean all

.PHONY: all clean
