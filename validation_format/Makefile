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

NAME	:=	libftprintf.a
LFT		:=	libft.a


PLATFORM:=	LINUX
CC		:=	gcc
CFLAGS	:=	-Wall -Werror -Wextra


ifeq ($(PLATFORM),LINUX)
DBFLAGS :=	-fsanitize=address
LIBASAN :=	-lasan
else
DBFLAGS :=	
LIBASAN :=	
endif


LFTSRCS :=


LFTOBJS :=	

HDRDIR	:=	./
LFTDIR	:=	./libft/
TSTDIR	:=	../tests/

HDRS	:=	ft_printf.h
SRCS	:=	ft_printf.c					\
			converters.c				\
			converter_utils_rdfmt.c		\
			utils_t_str.c				\
			handlers.c					\
			handler_utils_int.c			\
			handler_utils_str.c			\
			handler_utils_float.c		\
			handler_utils_float_prec.c

#blob for faster compile, fokken' moulenette
PATH_LFTSRCS :=	libft/src/math/conv/ft_atoi.c\
				libft/src/mem/ft_delete.c\
				libft/src/math/conv/ft_imaxtoa_base.c\
				libft/src/math/conv/ft_in_base.c\
				libft/src/math/conv/ft_itoa.c\
				libft/src/math/conv/ft_lftoa.c\
				libft/src/lst/ft_lstappend.c\
				libft/src/lst/ft_lstdel.c\
				libft/src/lst/ft_lstfold.c\
				libft/src/lst/ft_lstnew_no_copy.c\
				libft/src/math/op/ft_max.c\
				libft/src/mem/ft_memcpy.c\
				libft/src/mem/ft_ptrarrnew.c\
				libft/src/str/str_ip/ft_strappend.c\
				libft/src/str/str/ft_strcdup.c\
				libft/src/str/str/ft_strchr.c\
				libft/src/str/str/ft_strcnew.c\
				libft/src/str/str/ft_str_countchar.c\
				libft/src/str/str_ip/ft_strctrim_right_inplace.c\
				libft/src/str/str/ft_strdel.c\
				libft/src/str/str/ft_strdup.c\
				libft/src/str/str/ft_strequ.c\
				libft/src/str/str/ft_strfind.c\
				libft/src/str/str_ip/ft_strinsert.c\
				libft/src/str/str/ft_strlen.c\
				libft/src/str/strls/ft_strlsdel.c\
				libft/src/str/str_ip/ft_strmerge.c\
				libft/src/str/str/ft_strnew.c\
				libft/src/str/str_ip/ft_strpad_insert_inplace.c\
				libft/src/str/str/ft_strpad_left.c\
				libft/src/str/str_ip/ft_strpad_left_inplace.c\
				libft/src/str/str/ft_strpad_right.c\
				libft/src/str/str_ip/ft_strpad_right_inplace.c\
				libft/src/str/str_ip/ft_strprepend.c\
				libft/src/str/str/ft_strrchr.c\
				libft/src/str/str_ip/ft_strreplace_inplace.c\
				libft/src/str/str/ft_strrev.c\
				libft/src/str/str_ip/ft_strrev_inplace.c\
				libft/src/str/str/ft_strsub.c\
				libft/src/str/str/ft_str_toprint.c\
				libft/src/str/str_ip/ft_str_toupper.c\
				libft/src/mem/ft_swap.c\
				libft/src/math/conv/ft_uimaxtoa_base.c\
				libft/src/math/apa/ft_atovlq.c\
				libft/src/mem/ft_bzero.c\
				libft/src/math/conv/ft_digits_base.c\
				libft/src/str/char/ft_isdigit.c\
				libft/src/str/char/ft_islower.c\
				libft/src/str/char/ft_isprint.c\
				libft/src/str/char/ft_isspace.c\
				libft/src/math/conv/ft_is_valid_base.c\
				libft/src/math/conv/ft_itoa_base.c\
				libft/src/lst/ft_lstdelone.c\
				libft/src/mem/ft_memalloc.c\
				libft/src/mem/ft_memchr.c\
				libft/src/mem/ft_memdel.c\
				libft/src/mem/ft_memdup.c\
				libft/src/mem/ft_memset.c\
				libft/src/mem/ft_msb.c\
				libft/src/str/strls/ft_split.c\
				libft/src/str/str/ft_strcmp.c\
				libft/src/str/str_ip/ft_strctrim_left_inplace.c\
				libft/src/str/str/ft_stristr.c\
				libft/src/str/str/ft_strjoin.c\
				libft/src/str/str/ft_strlcpy.c\
				libft/src/str/str/ft_strreplace.c\
				libft/src/str/char/ft_toupper.c\
				libft/src/math/conv/ft_udigits_base.c\
				libft/src/math/conv/ft_uitoa_base.c\
				libft/src/math/apa/ft_vlq_bsr_acc.c\
				libft/src/math/apa/ft_vlqdel.c\
				libft/src/math/apa/ft_vlq_getpow10.c\
				libft/src/math/apa/ft_vlq_mul_acc.c\
				libft/src/math/apa/ft_vlqtoa_base.c\
				libft/src/math/op/ft_ilog2.c\
				libft/src/math/op/ft_ipowi.c\
				libft/src/mem/ft_memcmp.c\
				libft/src/mem/ft_not_msb.c\
				libft/src/io/ft_putendl_fd.c\
				libft/src/ft_str_base_to_base_expn.c\
				libft/src/str/str/ft_strcat.c\
				libft/src/str/str/ft_strcpy.c\
				libft/src/str/str_ip/ft_str_csubstitute.c\
				libft/src/str/strls/ft_strlsjoin.c\
				libft/src/str/strls/ft_strsplitstr.c\
				libft/src/math/apa/ft_vlq_add_acc.c\
				libft/src/math/apa/ft_vlq_bsr.c\
				libft/src/math/apa/ft_vlq_divmod.c\
				libft/src/math/apa/ft_vlqdup.c\
				libft/src/math/apa/ft_vlqlen.c\
				libft/src/math/apa/ft_vlq_mul.c\
				libft/src/math/apa/ft_vlqnew.c\
				libft/src/math/op/ft_abs.c\
				libft/src/math/conv/ft_is_valid_nbstr_in_base.c\
				libft/src/math/op/ft_min.c\
				libft/src/io/ft_putchar_fd.c\
				libft/src/io/ft_putstr_fd.c\
				libft/src/str/strls/ft_strdivide.c\
				libft/src/mem/ft_u64bits_itoj.c\
				libft/src/math/apa/ft_vlq_add.c\
				libft/src/math/apa/ft_vlq_bsl.c\
				libft/src/math/apa/ft_vlq_bsl_acc.c\
				libft/src/math/apa/ft_vlqcmp.c\
				libft/src/math/apa/ft_vlq_count_sigbit.c\
				libft/src/math/apa/ft_vlq_count_sigbit_of_part.c\
				libft/src/math/apa/ft_vlq_sub_acc.c\
				libft/src/math/apa/ft_vlqtrim.c\
				libft/src/math/apa/ft_vlq_sub.c
			

LFTSRCS :=	ft_atoi.c\
			ft_delete.c\
			ft_imaxtoa_base.c\
			ft_in_base.c\
			ft_itoa.c\
			ft_lftoa.c\
			ft_lstappend.c\
			ft_lstdel.c\
			ft_lstfold.c\
			ft_lstnew_no_copy.c\
			ft_max.c\
			ft_memcpy.c\
			ft_ptrarrnew.c\
			ft_strappend.c\
			ft_strcdup.c\
			ft_strchr.c\
			ft_strcnew.c\
			ft_str_countchar.c\
			ft_strctrim_right_inplace.c\
			ft_strdel.c\
			ft_strdup.c\
			ft_strequ.c\
			ft_strfind.c\
			ft_strinsert.c\
			ft_strlen.c\
			ft_strlsdel.c\
			ft_strmerge.c\
			ft_strnew.c\
			ft_strpad_insert_inplace.c\
			ft_strpad_left.c\
			ft_strpad_left_inplace.c\
			ft_strpad_right.c\
			ft_strpad_right_inplace.c\
			ft_strprepend.c\
			ft_strrchr.c\
			ft_strreplace_inplace.c\
			ft_strrev.c\
			ft_strrev_inplace.c\
			ft_strsub.c\
			ft_str_toprint.c\
			ft_str_toupper.c\
			ft_swap.c\
			ft_uimaxtoa_base.c\
			ft_atovlq.c\
			ft_bzero.c\
			ft_digits_base.c\
			ft_isdigit.c\
			ft_islower.c\
			ft_isprint.c\
			ft_isspace.c\
			ft_is_valid_base.c\
			ft_itoa_base.c\
			ft_lstdelone.c\
			ft_memalloc.c\
			ft_memchr.c\
			ft_memdel.c\
			ft_memdup.c\
			ft_memset.c\
			ft_msb.c\
			ft_split.c\
			ft_strcmp.c\
			ft_strctrim_left_inplace.c\
			ft_stristr.c\
			ft_strjoin.c\
			ft_strlcpy.c\
			ft_strreplace.c\
			ft_toupper.c\
			ft_udigits_base.c\
			ft_uitoa_base.c\
			ft_vlq_bsr_acc.c\
			ft_vlqdel.c\
			ft_vlq_getpow10.c\
			ft_vlq_mul_acc.c\
			ft_vlqtoa_base.c\
			ft_ilog2.c\
			ft_ipowi.c\
			ft_memcmp.c\
			ft_not_msb.c\
			ft_putendl_fd.c\
			ft_str_base_to_base_expn.c\
			ft_strcat.c\
			ft_strcpy.c\
			ft_str_csubstitute.c\
			ft_strlsjoin.c\
			ft_strsplitstr.c\
			ft_vlq_add_acc.c\
			ft_vlq_bsr.c\
			ft_vlq_divmod.c\
			ft_vlqdup.c\
			ft_vlqlen.c\
			ft_vlq_mul.c\
			ft_vlqnew.c\
			ft_abs.c\
			ft_is_valid_nbstr_in_base.c\
			ft_min.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_strdivide.c\
			ft_u64bits_itoj.c\
			ft_vlq_add.c\
			ft_vlq_bsl.c\
			ft_vlq_bsl_acc.c\
			ft_vlqcmp.c\
			ft_vlq_count_sigbit.c\
			ft_vlq_count_sigbit_of_part.c\
			ft_vlq_sub_acc.c\
			ft_vlqtrim.c\
			ft_vlq_sub.c

OBJS	:=	$(SRCS:.c=.o)
LFTOBJS	:=	$(LFTSRCS:.c=.o)
PATH_LFTOBJS := $(PATH_LFTSRCS:.c=.o)

MAIN	:=	main_asprintf.c
CAPSMAIN:=	main_asprintf_caps.c
VLQMAIN	:=	main_vlq.c
TEST	:=	test.out


RESET	:=	"\033[0m"
RED		:=	"\033[0;31m"
GREEN	:=	"\033[0;32m"


#$(NAME): $(LFTDIR)$(LFT) $(OBJS)
#	@printf "Compiling library: "$@" -> "$(RED)
#	@cp $< ./$@
#	@$(CC) $(CFLAGS) -c $(SRCS) -I$(HDRDIR)
#	@ar -r $@ $(OBJS)
#	@ranlib $@
#	@printf $(GREEN)"OK!"$(RESET)"\n"

# $(OBJS) $(PATH_LFTOBJS)
$(NAME):
	@$(CC) $(CFLAGS) -c $(SRCS) $(PATH_LFTSRCS) -I$(HDRDIR) -I./libft/hdr/
	@ar -r $@ $(OBJS) $(LFTOBJS)
	@ranlib $@

#blob
%.o:%.c
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) -I./libft/hdr/ -o $@

#dependencies are taken care of in libft's makefile.
$(LFTDIR)$(LFT): $(LFTSRCS)
	$(MAKE) -C $(LFTDIR) $(LFT)


all: $(NAME)

clean:
#	@printf "Calling libftprintf clean...\n"
	@$(MAKE) -C $(LFTDIR) clean
	@rm -f $(OBJS) $(LFTOBJS) $(PATH_LFTOBJS)
	@rm -f $(TSTDIR)$(MAIN:.c=.o) $(TSTDIR)$(CAPSMAIN:.c=.o) $(TSTDIR)$(VLQMAIN:.c=.o) $(TEST)

fclean:clean
#	@printf "Calling libftprintf fclean...\n"
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
