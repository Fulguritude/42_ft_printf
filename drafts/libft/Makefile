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

# Builds libft as a static library

NAME	=	libft.a

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

HDRDIR	=	./hdr/
SRCDIR	=	./src/
OBJDIR	=	./obj/
TSTDIR	=	../ #keep out of git bounds to avoid forbidden functions

HDRS	=	libft.h
SRCS	=	ft_memset.c					\
			ft_bzero.c					\
			ft_memcpy.c					\
			ft_memccpy.c				\
			ft_memmove.c				\
			ft_memalloc.c				\
			ft_memdel.c					\
			ft_memchr.c					\
			ft_memcmp.c					\
			ft_memdup.c					\
			ft_memhex.c					\
			ft_swap.c					\
			ft_delete.c					\
			ft_strlen.c					\
			ft_strnew.c					\
			ft_strlsnew.c				\
			ft_strdel.c					\
			ft_strlsdel.c				\
			ft_strrev.c					\
			ft_strclr.c					\
			ft_strdup.c					\
			ft_strcdup.c				\
			ft_strcpy.c					\
			ft_strncpy.c				\
			ft_strlcpy.c				\
			ft_strcmp.c					\
			ft_strncmp.c				\
			ft_strequ.c					\
			ft_strnequ.c				\
			ft_strchr.c					\
			ft_strrchr.c				\
			ft_strstr.c					\
			ft_strnstr.c				\
			ft_strcat.c					\
			ft_strncat.c				\
			ft_strlcat.c				\
			ft_strsub.c					\
			ft_strlssub.c				\
			ft_strpad_left.c			\
			ft_strpad_left_inplace.c	\
			ft_strlspad_left.c			\
			ft_strpad_right.c			\
			ft_strpad_right_inplace.c	\
			ft_strappend.c				\
			ft_strprepend.c				\
			ft_strjoin.c				\
			ft_strtrim.c				\
			ft_strsplit.c				\
			ft_strhex.c					\
			ft_strlsjoin.c				\
			ft_strdivide.c				\
			ft_str_countchar.c			\
			ft_strls_countchar.c		\
			ft_ptrarrlen.c				\
			ft_ptrarrnew.c				\
			ft_split.c					\
			ft_striter.c				\
			ft_striteri.c				\
			ft_strmap.c					\
			ft_strmapi.c				\
			ft_isalpha.c				\
			ft_isdigit.c				\
			ft_isalnum.c				\
			ft_isascii.c				\
			ft_isprint.c				\
			ft_isspace.c				\
			ft_toupper.c				\
			ft_tolower.c				\
			ft_max.c					\
			ft_min.c					\
			ft_umax.c					\
			ft_umin.c					\
			ft_atoi.c					\
			ft_itoa.c					\
			ft_in_base.c				\
			ft_is_valid_base.c			\
			ft_itoa_base.c				\
			ft_imaxtoa_base.c			\
			ft_uitoa_base.c				\
			ft_uimaxtoa_base.c			\
			ft_atoi_base.c				\
			ft_convert_base.c			\
			ft_digits.c					\
			ft_digits_base.c			\
			ft_udigits_base.c			\
			ft_putchar_fd.c				\
			ft_putstr_fd.c				\
			ft_putendl_fd.c				\
			ft_putnbr_fd.c				\
			ft_putstrls_fd.c			\
			ft_putchar.c				\
			ft_putstr.c					\
			ft_putendl.c				\
			ft_putnbr.c					\
			ft_putstrls.c				\
			ft_putllstelem_fd.c			\
			ft_putllst_fd.c				\
			ft_putllstelem.c			\
			ft_putllst.c				\
			ft_putnbr_llstelem_fd.c		\
			ft_putnbr_llst_fd.c			\
			ft_lstnew.c					\
			ft_lstnew_no_copy.c			\
			ft_lstdelone.c				\
			ft_lstdel.c					\
			ft_lstpop.c					\
			ft_lstadd.c					\
			ft_lstappend.c				\
			ft_lstsize.c				\
			ft_lstcpy.c					\
			ft_lstsub.c					\
			ft_lstiter.c				\
			ft_lstmap.c					\
			ft_lstget.c					\
			ft_lstfold.c				\
			ft_lststr_to_strls.c

OBJS	=	$(SRCS:.c=.o)

MAIN	=	main_libft.c
TEST	=	test.out

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

#@ before a function makes it so that its call isn't echoed to stdout
#$@ is a call to the string of the current rule
#$^ is a call to the string of the current dependencies
#$< is a call to the string of the first dependency in case of multiple deps

$(OBJDIR)%.o: $(SRCDIR)%.c
	@printf "Compiling file: "$@" -> "$(RED)
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(NAME): $(addprefix $(OBJDIR),$(OBJS))
	@printf "Compiling library: "$@" -> "$(RED)
	@ar -rc $@ $^
	@ranlib $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

all: $(NAME)

clean:
	@printf "Calling libft clean...\n"
	@rm -f $(addprefix $(OBJDIR),$(OBJS))

fclean: clean
	@printf "Calling libft fclean...\n"
	@rm -f $(NAME)

re:fclean all

build_test: re
	gcc $(TSTDIR)$(MAIN) $(NAME) -o $(TSTDIR)$(TEST)
	./$(TEST)
	rm -f $(TEST)

test:build_test
	@make clean
