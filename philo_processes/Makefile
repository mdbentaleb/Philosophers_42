# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/13 18:30:00 by moben-ta          #+#    #+#              #
#    Updated: 2025/06/19 13:35:27 by moben-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc 
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = utils_bonus.c ft_init_data_bonus.c destroy_sem_bonus.c \
		ft_routine_bonus.c ft_routine_utils_bonus.c main_bonus.c
OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c philo_bonus.h
	$(CC) $(CFLAGS) -c  -o $@ $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re