# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 21:33:56 by tduquesn          #+#    #+#              #
#    Updated: 2017/12/12 19:50:00 by tduquesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
LFT		=	libft.a

CFLAGS	=	-Wall -Werror -Wextra

HDDIR	=	.
LFTDIR	=	./libft/
TSTDIR	=	./tests/

HDRS	=	ft_printf.h
SRCS	=	ft_printf.c
TESTS	=	

OBJS	=	$(SRCS:.c=.o)

$(LFT):
	$(MAKE) -C $(LFTDIR) $(LIBFT)

$(NAME):
	gcc $(CFLAGS) -c $(SRCS)
	gcc -o $(NAME) $(OBJS) -lft -L$(LFTDIR)

all: $(LFT) $(NAME)

clean:
	rm -f $(OBJS)

fclean:clean
	$(MAKE) -C $(LFTDIR) fclean
	rm -f $(NAME)

re:fclean all

test:re
	./$(NAME) $(addprefix $(TSTDIR),$(TESTS))
	@make clean
