##
## Makefile for  in /home/zellou_i/rendu/PSU_2013_philo
## 
## Made by ilyas zelloufi
## Login   <zellou_i@epitech.net>
## 
## Started on  Mon Jul  7 13:11:25 2014 ilyas zelloufi
## Last update Mon Jul  7 13:11:26 2014 ilyas zelloufi
##

NAME	= philo

SRC	= main.c \
	  manage_table.c

OBJ	= $(SRC:.c=.o)

CC	= gcc

CFLAGS	= -W -Wall -Wextra -ansi -pedantic -lpthread

RM	= rm -f
ECHO	= echo -e

all	:  $(NAME)

$(NAME)	: $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@$(ECHO) '\033[0;32m> Compiled\033[0m'

clean	:
	@$(RM) $(OBJ)
	@$(RM) *~
	@$(RM) \#*#
	@$(ECHO) '\033[0;31m> Directory cleaned\033[0m'


fclean	: clean
	@$(RM) $(NAME)
	@$(ECHO) '\033[0;31m> Remove executable\033[0m'

re	: fclean  all

.PHONY	: all clean fclean re
