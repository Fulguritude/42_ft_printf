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
			handler_utils_float.c
OBJS	=	$(SRCS:.c=.o)

MAIN	=	main.c
BONUS	=	main_bonus.c
ASMAIN	=	main_asprintf.c
BNBMAIN	=	main_bignb.c
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
	@rm -f $(TSTDIR)$(BONUS:.c=.o)
	@rm -f $(TSTDIR)$(ASMAIN:.c=.o)
	@rm -f $(TSTDIR)$(BNBMAIN:.c=.o)
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
	@$(CC) $(OBJS) $(TSTDIR)$(MAIN:.c=.o) -lftprintf -L./ -lasan -o $(TEST)
	./$(TEST)
	@make clean
	@printf "Done !\n"

bonus:fclean $(NAME)
	@printf "Rebuilding test.out for rule 'bonus'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(BONUS) -o $(TSTDIR)$(BONUS:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(BONUS:.c=.o) -lftprintf -L./ -lasan -o $(TEST)
	./$(TEST)
	@make clean
	@printf "Done !\n"

astest:fclean $(NAME)
	@printf "Rebuilding test.out for rule 'astest'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(ASMAIN) -o $(TSTDIR)$(ASMAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(ASMAIN:.c=.o) -lftprintf -L./ -lasan -o $(TEST)
	./$(TEST)
	@make clean
	@printf "Done !\n"

vgastest:fclean $(NAME)
	@printf "Rebuilding test.out for rule 'vgastest'...\n"
	@$(CC) $(CFLAGS) -c $(TSTDIR)$(ASMAIN) -o $(TSTDIR)$(ASMAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(ASMAIN:.c=.o) -lftprintf -L./ -o $(TEST)
	valgrind -v --track-origins=yes ./$(TEST)
	@make clean
	@printf "Done !\n"

vgleakastest:fclean $(NAME)
	@printf "Rebuilding test.out for rule 'vgleakastest'...\n"
	@$(CC) $(CFLAGS) -c $(TSTDIR)$(ASMAIN) -o $(TSTDIR)$(ASMAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(ASMAIN:.c=.o) -lftprintf -L./ -o $(TEST)
	valgrind -v --track-origins=yes --leak-check=full ./$(TEST)
	@make clean
	@printf "Done !\n"

bignbtest:$(NAME)
	@printf "Rebuilding test.out for rule 'bignbtest'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(BNBMAIN) -o $(TSTDIR)$(BNBMAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(BNBMAIN:.c=.o) -lftprintf -L./ -lasan -o $(TEST)
	./$(TEST)
	@make clean
	@printf "Done !\n"

.PHONY: all clean re
