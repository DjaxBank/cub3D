# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/30 16:22:59 by dbank             #+#    #+#              #
#    Updated: 2025/06/30 16:24:24 by dbank            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Generated using 42 tools, manual changes may be overwritten

## Commands ##

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./inc -I./ -g -fsanitize=address,undefined
LDFLAGS = -L./libft

## Files ##

SRCS 	= src/parse.c src/rendering.c src/main.c src/raycaster.c \
		 src/parse.c src/parse_utils_a.c src/parse_utils_b.c src/elements.c \
	   src/validate.c src/init.c
OBJS = $(SRCS:src/%.c=obj/%.o)

## Configuration ##

NAME = cube3d

## Compilation rules ##

$(NAME): $(OBJS) libft/libft.a build/libmlx42.a
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

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
	cmake -S MLX42 -B build 
	cmake --build build