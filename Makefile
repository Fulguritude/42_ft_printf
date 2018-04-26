# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 21:33:56 by tduquesn          #+#    #+#              #
#    Updated: 2018/04/26 15:35:27 by tduquesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
LFT		=	libft.a


PLATFORM=	MAC_OS
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra


ifeq ($(PLATFORM),LINUX)
DBFLAGS =	-fsanitize=address
LIBASAN =	-lasan
else
DBFLAGS =	
LIBASAN =	
endif


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


RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"


$(NAME): $(LFTDIR)$(LFT) $(OBJS)
	@printf "Compiling library: "$@" -> "$(RED)
	@cp $< ./$@
	@$(CC) $(CFLAGS) -c $(SRCS) -I$(HDRDIR)
	@ar -r $@ $(OBJS)
	@ranlib $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

#dependencies are taken care of in libft's makefile.
$(LFTDIR)$(LFT):
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
	@printf "\tRebuilding test.out for rule 'test' for '"$(PLATFORM)"'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(MAIN) -o $(TSTDIR)$(MAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(MAIN:.c=.o) -lftprintf -L./ $(LIBASAN) -o $(TEST)
	@printf "\tDone ! Usage: "$(GREEN)"./test.out {value|NULL}"$(RESET)"\n"

capstest:$(NAME)
	@printf "\tRebuilding test.out for rule 'capstest' for '"$(PLATFORM)"'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(CAPSMAIN) -o $(TSTDIR)$(CAPSMAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(CAPSMAIN:.c=.o) -lftprintf -L./ $(LIBASAN) -o $(TEST)
	@printf "\tDone ! Usage: "$(GREEN)"./test.out {value|NULL}"$(RESET)"\n"

vlqtest:$(NAME)
	@printf "\tRebuilding test.out for rule 'vlqtest' for '"$(PLATFORM)"'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(VLQMAIN) -o $(TSTDIR)$(VLQMAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(VLQMAIN:.c=.o) -lftprintf -L./ $(LIBASAN) -o $(TEST)
	./$(TEST)
	@make clean
	@printf "\tDone !\n"

mf_debug:
	@cat -e -t -v Makefile

.PHONY: all clean re test vlqtest capstest
