# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 21:33:56 by tduquesn          #+#    #+#              #
#    Updated: 2018/02/26 19:15:56 by fulguritu        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Builds libft as a static library

NAME	=	libft.a


CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra


HDRDIR	=	./hdr/


SRCDIR	=	./src/

SRCDIR_MEM	= mem/

SRCDIR_IO	= io/

SRCDIR_STR	= str/
SRCDIR_STR_CHR = char/
SRCDIR_STR_STR = str/
SRCDIR_STR_SIP = str_ip/
SRCDIR_STR_SLS = strls/

SRCDIR_LST	= lst/

SRCDIR_MATH	= math/
SRCDIR_MATH_CV = conv/
SRCDIR_MATH_OP = op/
SRCDIR_MATH_BN = bignb/


OBJDIR	=	./obj/

TSTDIR	=	../ #keep out of git bounds to avoid forbidden functions



HDRS	=	libft.h						\
			libft_mem.h					\
			libft_io.h					\
			libft_str.h					\
			libft_math.h				\
			libft_lst.h


SRC_MEM_MEM	=	ft_memset.c					\
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
				ft_u64bits_itoj.c			\
				ft_ptrarrlen.c				\
				ft_ptrarrnew.c

SRC_MEM	=	$(addprefix $(SRCDIR_MEM), $(SRC_MEM_MEM))

SRC_STR_CHR	=	ft_isalpha.c				\
				ft_isupper.c				\
				ft_islower.c				\
				ft_isdigit.c				\
				ft_isalnum.c				\
				ft_isascii.c				\
				ft_isprint.c				\
				ft_isspace.c				\
				ft_toupper.c				\
				ft_tolower.c

SRC_STR_STR	=	ft_strlen.c					\
				ft_strnew.c					\
				ft_strcnew.c				\
				ft_strrev.c					\
				ft_strhex.c					\
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
				ft_strfind.c				\
				ft_strstr.c					\
				ft_strnstr.c				\
				ft_stristr.c				\
				ft_strcat.c					\
				ft_strncat.c				\
				ft_strlcat.c				\
				ft_strsub.c					\
				ft_strpad_left.c			\
				ft_strpad_right.c			\
				ft_strjoin.c				\
				ft_strreplace.c				\
				ft_strtrim.c				\
				ft_strremove.c				\
				ft_strreplace.c				\
				ft_str_toprint.c			\
				ft_str_countchar.c			\
				ft_striter.c				\
				ft_striteri.c				\
				ft_strmap.c					\
				ft_strmapi.c				\
				ft_strdel.c

SRC_STR_SIP	=	ft_strmerge.c				\
				ft_strappend.c				\
				ft_strprepend.c				\
				ft_strinsert.c				\
				ft_strreplace_inplace.c		\
				ft_strrev_inplace.c			\
				ft_str_csubstitute.c		\
				ft_str_toupper.c			\
				ft_strsub_rm_inplace.c		\
				ft_strpad_left_inplace.c	\
				ft_strpad_right_inplace.c	\
				ft_strpad_insert_inplace.c	\
				ft_strctrim_left_inplace.c	\
				ft_strctrim_right_inplace.c	\
				ft_strntrim_left_inplace.c	\
				ft_strntrim_right_inplace.c

SRC_STR_SLS =	ft_strlsnew.c				\
				ft_strlscnew.c				\
				ft_strcsplit.c				\
				ft_split.c					\
				ft_strsplitstr.c			\
				ft_strdivide.c				\
				ft_strlspad_left.c			\
				ft_strlsjoin.c				\
				ft_strlssub.c				\
				ft_strls_countchar.c		\
				ft_strlsmap.c				\
				ft_strlsmap_inplace.c		\
				ft_strlsdel.c

SRC_STR =	$(addprefix $(SRCDIR_STR), \
				$(addprefix $(SRCDIR_STR_CHR),$(SRC_STR_CHR))	\
				$(addprefix $(SRCDIR_STR_STR),$(SRC_STR_STR))	\
				$(addprefix $(SRCDIR_STR_SIP),$(SRC_STR_SIP))	\
				$(addprefix $(SRCDIR_STR_SLS),$(SRC_STR_SLS))	\
			)

SRC_LST_LST	=	ft_lstnew.c					\
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

SRC_LST	=	$(addprefix $(SRCDIR_LST), $(SRC_LST_LST))

SRC_IO_IO	=	ft_putchar_fd.c				\
				ft_putstr_fd.c				\
				ft_putendl_fd.c				\
				ft_putnbr_fd.c				\
				ft_putstrls_fd.c			\
				ft_putchar.c				\
				ft_putstr.c					\
				ft_putendl.c				\
				ft_putnbr.c					\
				ft_putmem.c					\
				ft_putmem_fd.c				\
				ft_putstrls.c				\
				ft_putlstelem_fd.c			\
				ft_putlst_fd.c				\
				ft_putlstelem.c				\
				ft_putlst.c					\
				ft_putnbr_lstelem_fd.c		\
				ft_putnbr_lst_fd.c			

SRC_IO	=	$(addprefix $(SRCDIR_IO), $(SRC_IO_IO))

SRC_MATH_CV	=	ft_atoi.c					\
				ft_itoa.c					\
				ft_in_base.c				\
				ft_is_valid_base.c			\
				ft_is_valid_nbstr_in_base.c \
				ft_itoa_base.c				\
				ft_imaxtoa_base.c			\
				ft_uitoa_base.c				\
				ft_uimaxtoa_base.c			\
				ft_atoi_base.c				\
				ft_atoui_base.c				\
				ft_convert_base.c			\
				ft_uconvert_base.c			\
				ft_digits.c					\
				ft_digits_base.c			\
				ft_udigits_base.c

SRC_MATH_OP	=	ft_max.c					\
				ft_min.c					\
				ft_umax.c					\
				ft_umin.c					\
				ft_floor.c					\
				ft_ceil.c					\
				ft_ipowi.c					\
				ft_lfpowi.c					\
				ft_ilog2.c					\
				ft_exp.c					\
				ft_ln.c						\
				ft_logn.c

SRC_MATH_BN =	ft_bignbnew.c						\
				ft_bignbdup.c						\
				ft_atobignb.c						\
				ft_bignb_strcmp.c					\
				ft_bignb_iszero.c					\
				ft_bignb_to_str.c					\
				ft_bignb_vlq_updates_revns.c		\
				ft_bignb_revns_updates_vlq.c		\
				ft_bignb_str_base2bin_inplace.c		\
				ft_bignb_str_bin2base_inplace.c		\
				ft_bignbdel.c						\
				ft_bignb_add.c						\
				ft_bignb_sub.c						\
				ft_bignb_mul.c						\
				ft_bignb_str_add.c					\
				ft_bignb_str_sub.c					\
				ft_bignb_str_mul.c					\
				ft_bignb_str_div.c					\
				ft_bignb_add_acc.c					\
				ft_bignb_sub_acc.c					\
				ft_bignb_div_acc.c					\
				ft_vlqnew.c						\
				ft_atovlq.c						\
				ft_vlqdup.c						\
				ft_vlq_getpow2.c				\
				ft_vlq_getpow10.c				\
				ft_vlqtoa_base.c				\
				ft_vlqlen.c						\
				ft_vlqcmp.c						\
				ft_vlq_count_sigbit.c			\
				ft_vlq_count_sigbit_of_part.c	\
				ft_vlqhex.c						\
				ft_vlqtrim.c					\
				ft_vlqdel.c						\
				ft_vlq_add.c					\
				ft_vlq_sub.c					\
				ft_vlq_mul.c					\
				ft_vlq_div.c					\
				ft_vlq_divmod.c					\
				ft_vlq_pow.c					\
				ft_vlq_bsl.c					\
				ft_vlq_bsr.c					\
				ft_vlq_add_acc.c				\
				ft_vlq_sub_acc.c				\
				ft_vlq_mul_acc.c				\
				ft_vlq_bsl_acc.c				\
				ft_vlq_bsr_acc.c				\
				ft_vlq_getpow10.c
				#ft_vlq_bwa.c
				#ft_vlq_bwo.c

SRC_MATH=	$(addprefix $(SRCDIR_MATH), \
				$(addprefix $(SRCDIR_MATH_CV),$(SRC_MATH_CV))	\
				$(addprefix $(SRCDIR_MATH_OP),$(SRC_MATH_OP))	\
				$(addprefix $(SRCDIR_MATH_BN),$(SRC_MATH_BN))	\
			)

SRC_TMP	=	ft_ftoa.c						\
			ft_ftoa_base.c					\
			ft_lftoa_base.c					\
			ft_lftoa.c						\
			ft_vlq_get_greatest_sub_pow10.c \
			ft_vlq_abstractval_as_hex.c		\
			ft_str_base_to_base_expn.c		\
			ft_str_base_expn_to_base.c

SRCS	=	$(SRC_MEM)		\
			$(SRC_STR)		\
			$(SRC_LST)		\
			$(SRC_IO)		\
			$(SRC_MATH)		\
			$(SRC_TMP)

OBJS	=	$(SRCS:.c=.o)

MAIN	=	main_libft.c
TEST	=	test.out

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"


#https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#@ before a function makes it so that its call isn't echoed to stdout
#$@ is a call to the string of the current rule
#$^ is a call to the string of the current dependencies
#$< is a call to the string of the first dependency in case of multiple deps

$(NAME):mkobjstruct $(addprefix $(OBJDIR)$,$(OBJS))
	@printf "Compiling library: "$@" -> "$(RED)
	@ar -rc $@ $(addprefix $(OBJDIR)$,$(OBJS))
	@ranlib $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o:$(SRCDIR)%.c
	@printf "Compiling file: "$@" -> "$(RED)
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) -o $@
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

mkobjstruct:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)$(SRCDIR_IO)
	@mkdir -p $(OBJDIR)$(SRCDIR_MEM)
	@mkdir -p $(OBJDIR)$(SRCDIR_LST)
	@mkdir -p $(OBJDIR)$(SRCDIR_STR)
	@mkdir -p $(OBJDIR)$(SRCDIR_STR)$(SRCDIR_STR_CHR)
	@mkdir -p $(OBJDIR)$(SRCDIR_STR)$(SRCDIR_STR_STR)
	@mkdir -p $(OBJDIR)$(SRCDIR_STR)$(SRCDIR_STR_SIP)
	@mkdir -p $(OBJDIR)$(SRCDIR_STR)$(SRCDIR_STR_SLS)
	@mkdir -p $(OBJDIR)$(SRCDIR_MATH)
	@mkdir -p $(OBJDIR)$(SRCDIR_MATH)$(SRCDIR_MATH_CV)
	@mkdir -p $(OBJDIR)$(SRCDIR_MATH)$(SRCDIR_MATH_OP)
	@mkdir -p $(OBJDIR)$(SRCDIR_MATH)$(SRCDIR_MATH_BN)

test:build_test
	@make clean
