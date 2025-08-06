# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbank <dbank@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2025/06/30 16:22:59 by dbank         #+#    #+#                  #
#    Updated: 2025/08/06 14:08:55 by showard       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


## Commands ##

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./inc -I./ -O3 -ffast-math -flto
LDFLAGS = -L./libft -L./build

## Files ##

SRCS = src/rendering.c src/main.c src/raycaster.c \
	src/parse.c src/parse_utils_a.c src/parse_utils_b.c src/elements.c \
	src/validate.c src/init.c src/put_wall.c src/minimap.c src/loop.c src/movement.c \
	src/minimap_fov.c src/doors.c src/raycaster_utils.c src/mouse_movement.c \
	src/raycaster_door.c src/collision.c src/movement_cases.c

OBJS = $(SRCS:src/%.c=obj/%.o)

## Configuration ##

NAME = cub3D

## Compilation rules ##

all: $(NAME)

$(NAME): libft/libft.a build/libmlx42.a $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) -lft -lmlx42 -ldl -lglfw -pthread -lm

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

## Cleaning rules ##

clean:
	$(RM) -rf obj
	$(MAKE) -C libft clean

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)
	$(RM) -rf build
	$(RM) -rf MLX42

re: fclean all

## Libraries ##

libft/libft.a:
	$(MAKE) -C libft all

build/libmlx42.a:
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@mkdir -p build
	cmake -S MLX42 -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build -j4

.PHONY: all clean fclean re