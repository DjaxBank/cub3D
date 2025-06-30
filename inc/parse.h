#include "libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>

#ifndef PARSE_H
# define PARSE_H
# define RED 0
# define GREEN 1
# define BLUE 2

#include "game.h"

void	map_init(t_data *state);
bool input_check(char *str, t_data *state);
#endif