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
SRCS	=	ft_printf.c					\
			converters.c				\
			converter_utils_rdfmt.c		\
			utils_t_str.c				\
			handlers.c					\
			handler_utils_int.c			\
			handler_utils_unicode.c		\
			handler_utils_float.c
OBJS	=	$(SRCS:.c=.o)

MAIN	=	main.c
BONUS	=	main_bonus.c
TEST	=	test.out

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
	@rm -f $(TSTDIR)$(BONUS:.c=.o)
	@rm -f $(TEST)

fclean:clean
	@printf "Calling libftprintf fclean...\n"
	@rm -f $(LFTDIR)$(LFT)
	@rm -f $(NAME)

re:fclean all

#remove CFLAGS below before testing weirder undefined printf cases
test:fclean $(NAME)
	@printf "Rebuilding test.out for rule 'test'...\n"
	@$(CC) $(CFLAGS) -c $(TSTDIR)$(MAIN) -o $(TSTDIR)$(MAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(MAIN:.c=.o) -lftprintf -L./ -o $(TEST)
	./$(TEST)
	@make clean
	@printf "Done !\n"

bonus:fclean $(NAME)
	@printf "Rebuilding test.out for rule 'bonus'...\n"
	@$(CC) $(CFLAGS) -c $(TSTDIR)$(BONUS) -o $(TSTDIR)$(BONUS:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(BONUS:.c=.o) -lftprintf -L./ -o $(TEST)
	./$(TEST)
	@make clean
	@printf "Done !\n"
