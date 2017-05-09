#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imarakho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/18 15:33:46 by imarakho          #+#    #+#              #
#    Updated: 2017/03/27 16:52:19 by imarakho         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d
SRC = main.c \
	read.c \
	get_next_line.c \
	wolf.c \
	draw.c \
	hooks.c \
	textures.c \
	floor.c \

LIB = -O3 libft/libft.a
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -g
MLX_F = -g -lmlx -framework OpenGL -O3 -framework AppKit
all: $(NAME)
$(NAME): $(OBJ)
	@make -C libft/ && make -C libft/ clean
	@clang $(FLAGS) $(MLX_F) $(LIB) $(OBJ) -o $(NAME)
	@echo "Compilation done!"
%.o: %.c
	@clang -O3 -c $(FLAGS) -o $@ $<
lldb:
	@clang -g $(FLAGS) $(MLX_F) $(LIB) $(SRC) -o debug
	@echo "Use 'debug' for lldb."
lclean:
	@rm -f debug
	@echo "'debug' removed!"
clean:
	@rm -f $(OBJ)
	@echo "Objects removed!"
fclean: clean
	@rm -f $(NAME)
	@echo "Executable removed!"
re: fclean all
