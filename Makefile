# Generated using 42 tools, manual changes may be overwritten

## Commands ##

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./inc -I./
LDFLAGS = -L./libft
RM = rm -f

## Files ##

SRCS = src/parse.c
OBJS = $(SRCS:src/%.c=obj/%.o)

## Configuration ##

NAME = cube3d

## Compilation rules ##

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

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

re: fclean $(NAME)

## Libraries ##

libft/libft.a:
	$(MAKE) -C libft all
