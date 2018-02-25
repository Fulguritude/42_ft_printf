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
			str_formatter.c			\
			utils_t_str.c			\
			handlers.c				\
			utils_int_handler.c
MAIN	=	main.c
TEST	=	test.out

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
	@printf "Calling libftprintf clean...\n"
	@$(MAKE) -C $(LFTDIR) clean
	@rm -f $(OBJS)
	@rm -f $(TSTDIR)$(MAIN:.c=.o)
	@rm -f $(TEST)

fclean:clean
	@printf "Calling libftprintf fclean...\n"
	@rm -f $(LFTDIR)$(LFT)
	@rm -f $(NAME)

re:fclean all

#remove CFLAGS below before testing weirder undefined printf cases
test:fclean $(NAME)
	@printf "Rebuilding test.out...\n"
	@$(CC) $(CFLAGS) -c $(TSTDIR)$(MAIN) -o $(TSTDIR)$(MAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(MAIN:.c=.o) -lftprintf -L./ -o $(TEST)
	./$(TEST)
	@make clean
	@printf "Done !\n"
