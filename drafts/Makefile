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
SRCS	=	ft_printf.c				\
			converters.c			\
			unicode.c				\
			utils_format_string.c	\
			utils_t_str.c			\
			handlers.c				\
			utils_int_handler.c
MAIN	=	main.c

OBJS	=	$(SRCS:.c=.o)

$(LFT):
	$(MAKE) -C $(LFTDIR) $(LFT)

$(NAME):
	gcc $(CFLAGS) -c $(SRCS) -I$(HDDIR)
	ar rc $(NAME) $(OBJS) -lft -L$(LFTDIR)
	ranlib $(NAME)

all: $(LFT) $(NAME)

clean:
	rm -f $(OBJS)

fclean:clean
	$(MAKE) -C $(LFTDIR) fclean
	rm -f $(NAME)

re:fclean all

test: $(LFT)
	gcc $(CFLAGS) -c $(SRCS) $(TSTDIR)$(MAIN)
	gcc $(OBJS) main.o -lft -L$(LFTDIR)
	./a.out
	@make clean
	@rm a.out
