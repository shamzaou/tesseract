# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/29 21:01:57 by alabdull           #+#    #+#              #
#    Updated: 2024/04/29 00:01:38 by shamzaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =   main.c \
	rendering/line.c \
	rendering/mlx_draw.c \
	rendering/player_actions.c \
	rendering/player_mouvements.c \
	rendering/queue.c \
	rendering/ray_intersection.c \
	rendering/raycasting.c \
	rendering/rendering.c \
	setup/free.c \
	setup/hooks.c \
	setup/init.c \
	setup/init_images.c \
	setup/map_error_handling.c \
	setup/map_validation.c \
	setup/map.c \
	setup/parse_line.c \
	setup/parsing_helpers.c \
	setup/parsing_validation.c \
	setup/parsing.c

NAME = cub3d

OBJ = $(SRC:.c=.o)

CC = CC

CFLAGS = -g3 -O3

# -fsanitize=address
# -Wall -Werror -Wextra

MLX = libmlx.dylib

LIB = libft/libft.a

PRINTF = libft/ft_printf/libftprintf.a

GNL = ./libft/get_next_line/getnextline.a

%.o: %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

all: $(NAME)

$(OBJ): %.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(MLX) $(OBJ)
	@make -sC ./libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(PRINTF) $(GNL) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(MLX):
	@make -sC ./mlx

clean:
	@rm -f $(OBJ)
	@rm -f $(MLX)
	@make clean -sC ./mlx
	@make clean -sC ./libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC ./libft

re: fclean all
