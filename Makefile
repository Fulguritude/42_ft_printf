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
DBFLAGS =	-fsanitize=address

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
			handler_utils_str.c			\
			handler_utils_float.c		\
			handler_utils_float_prec.c
OBJS	=	$(SRCS:.c=.o)

MAIN	=	main_asprintf.c
CAPSMAIN=	main_asprintf_caps.c
VLQMAIN	=	main_vlq.c
TEST	=	test.out

$(NAME): $(LFT) $(OBJS)
	@printf "Compiling library: "$@" -> "$(RED)
	@cp $(LFTDIR)$(LFT) ./$@
	@$(CC) $(CFLAGS) -c $(SRCS) -I$(HDRDIR)
	@ar -r $@ $(OBJS)
	@ranlib $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

#dependencies are taken care of in libft's makefile.
$(LFT):
	$(MAKE) -C $(LFTDIR) $(LFT)

all: $(NAME)

clean:
	@printf "Calling libftprintf clean...\n"
	@$(MAKE) -C $(LFTDIR) clean
	@rm -f $(OBJS)
	@rm -f $(TSTDIR)$(MAIN:.c=.o)
	@rm -f $(TSTDIR)$(CAPSMAIN:.c=.o)
	@rm -f $(TSTDIR)$(VLQMAIN:.c=.o)
	@rm -f $(TEST)

fclean:clean
	@printf "Calling libftprintf fclean...\n"
	@rm -f $(LFTDIR)$(LFT)
	@rm -f $(NAME)

re:fclean all

#remove CFLAGS below before testing weirder undefined printf cases
test:$(NAME)
	@printf "Rebuilding test.out for rule 'test'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(MAIN) -o $(TSTDIR)$(MAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(MAIN:.c=.o) -lftprintf -L./ -lasan -o $(TEST)
	@printf "Done ! Usage: ""\033[0;32m""./test.out {value|NULL}""\033[0m""\n"

capstest:$(NAME)
	@printf "Rebuilding test.out for rule 'capstest'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(CAPSMAIN) -o $(TSTDIR)$(CAPSMAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(CAPSMAIN:.c=.o) -lftprintf -L./ -lasan -o $(TEST)
	@printf "Done ! Usage: ""\033[0;32m""./test.out {value|NULL}""\033[0m""\n"

vlqtest:$(NAME)
	@printf "Rebuilding test.out for rule 'vlqtest'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(VLQMAIN) -o $(TSTDIR)$(VLQMAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(VLQMAIN:.c=.o) -lftprintf -L./ -lasan -o $(TEST)
	./$(TEST)
	@make clean
	@printf "Done !\n"

.PHONY: all clean re test vlqtest
