# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 21:33:56 by tduquesn          #+#    #+#              #
#    Updated: 2018/02/20 16:20:25 by tduquesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
LFT		=	libft.a

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

HDRDIR	=	./
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

#dependencies are taken care of in libft's makefile.
$(LFT):
	$(MAKE) -C $(LFTDIR) $(LFT)

$(NAME): $(LFT) $(OBJS)
	@printf "Compiling library: "$@" -> "$(RED)
	@cp $(LFTDIR)$(LFT) ./$@
	@$(CC) $(CFLAGS) -c $(SRCS) -I$(HDRDIR)
	@ar -r $@ $(OBJS)
	@ranlib $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

all: $(NAME)

clean:
	$(MAKE) -C $(LFTDIR) clean
	rm -f $(OBJS)

fclean:clean
	$(MAKE) -C $(LFTDIR) fclean
	rm -f $(NAME)

re:fclean all

#remove CFLAGS below before testing weirder undefined printf cases
test:fclean $(NAME)
	@printf "Rebuilding test.out...\n"
	@$(CC) $(CFLAGS) -c $(TSTDIR)$(MAIN) -o $(TSTDIR)$(MAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(MAIN:.c=.o) -lftprintf -L./ -o test.out
	./test.out
	@make clean
	@rm test.out
