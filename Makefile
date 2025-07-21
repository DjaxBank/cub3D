# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/30 16:22:59 by dbank             #+#    #+#              #
#    Updated: 2025/07/21 17:48:14 by dbank            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Generated using 42 tools, manual changes may be overwritten

## Commands ##

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./inc -I./ -O3 -ffast-math -flto
LDFLAGS = -L./libft

## Files ##

SRCS 	= src/rendering.c src/main.c src/raycaster.c \
		 src/parse.c src/parse_utils_a.c src/parse_utils_b.c src/elements.c \
	   src/validate.c src/init.c src/put_wall.c src/minimap.c src/loop.c src/movement.c \
	   src/minimap_fov.c src/doors.c src/raycaster_utils.c
OBJS = $(SRCS:src/%.c=obj/%.o)

## Configuration ##

NAME = cub3d

## Compilation rules ##

$(NAME): libft/libft.a build/libmlx42.a $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) libft/libft.a build/libmlx42.a -ldl -lglfw -pthread -lm

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

## Cleaning rules ##

clean:
	$(RM) $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(OBJS) $(NAME)
	$(MAKE) -C libft fclean
	rm -rf build

re: fclean $(NAME)

## Libraries ##

libft/libft.a:
	$(MAKE) -C libft all

build/libmlx42.a:
	git submodule init
	git submodule update
	cmake -S MLX42 -B build 
	cmake --build build