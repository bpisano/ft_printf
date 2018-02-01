# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: bpisano <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/01/31 12:15:53 by bpisano      #+#   ##    ##    #+#        #
#    Updated: 2018/02/01 18:12:38 by bpisano     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ./sources/ft_printf.c				\
	  ./sources/ft_strset.c				\
	  ./sources/ft_ctos.c				\
	  ./sources/ft_itoa_base_arg.c		\
	  ./sources/alpha_type_manager.c	\
	  ./sources/num_type_manager.c		\
	  ./sources/string_manager.c		\
	  ./sources/arg_manager.c			\
	  ./sources/arg_setter.c			\
	  ./sources/buffer_manager.c		\
	  ./sources/buffer_properties.c		\
	  ./sources/percent_buffer.c		\
	  ./sources/flag_manager.c			\
	  ./sources/value_manager.c			\

LIBSRC = ./libft/*.c

OBJECTS = $(SRC:.c=.o)

LIB = libft.a

HEADS = -I ./includes					\
		-I ./libft						\

FLAGS = -Wall -Werror -Wextra

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
END = \033[0m

all: $(NAME)

$(LIB):
	@(make -C libft)

$(NAME): $(LIB) $(OBJECTS)
	@cp libft/$(LIB) $(NAME)
	@ar rc $(NAME) $(OBJECTS)
	@echo "$(BLUE)$(NAME)\033[500D\033[42C$(GREEN)[DONE]$(END)"

%.o : %.c
	@echo "Compiling $(notdir $@)\033[500D\033[42C$(RED)[KO]$(END)"
	@gcc $(FLAGS) $(HEADS) -o $@ -c $?
	@echo "\033[1A\033[500D\033[42C$(GREEN)[DONE]$(END)"

clean:
	@rm -f $(OBJECTS)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@rm -f a.out
	@make fclean -C libft

re: fclean all
