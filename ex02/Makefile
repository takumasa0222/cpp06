# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/25 00:33:24 by tamatsuu          #+#    #+#              #
#    Updated: 2026/07/28 16:08:31 by tamatsuu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = real
CC = c++
INCLUDES = -I ./
CFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
SRCS    =   main.cpp \
			Base.cpp 
OBJS    = $(SRCS:.cpp=.o)
LIBDIR  = 
LIBS    = 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBDIR) $(LIBS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
all: $(NAME)

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 