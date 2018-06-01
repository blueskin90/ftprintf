# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/12 01:24:53 by toliver           #+#    #+#              #
#    Updated: 2018/05/30 19:35:56 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Werror -Wextra -Wall

FILES = ft_printf \
		parsing \
		bufferhandling \
		buff_fill1 \
		parse_flag1 \
		parse_flag2 \
		parse_conv1 \
		parse_conv2 \
		parse_size \
		parse_size1 \
		get_arg1 \
		buff_fillfloat \
		buff_fillbinary \
		buff_fillutility \
		buff_fillchar \
		buff_fillhexaoct \
		buff_fillfloat \
		buff_fillfloat_exp \
		buff_fillfloat_deci \
		bigint_handle \
#		buff_fillfloat_init \
#		buff_fillfloat_split \
#		buff_fillfloat_utility \
#		buff_fillfloat_rounding \

SRC = $(addsuffix .c,  $(FILES))

SRC_PATH = srcs/

SRCS = $(addprefix $(SRC_PATH),$(SRC))

OBJ_PATH = objs/

OBJS = $(addprefix $(OBJ_PATH),$(SRC:.c=.o))

INCLUDES = -I./includes

HEADERS = includes/libftprintf.h \


.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	ar rcs $(NAME) $(OBJS)

objs/%.o: srcs/%.c $(HEADERS)
	gcc -o $@ -c $< $(FLAGS) $(INCLUDES)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

test : $(NAME)
	gcc main.c -o test.out $(FLAGS) $(NAME) $(INCLUDES)

testnof : $(NAME)
	gcc main.c -o test.out $(NAME) $(INCLUDES)

cur : $(NAME)
	cp libftprintf.a ../../curqui_test
	make -C ../../curqui_test

re: fclean all
