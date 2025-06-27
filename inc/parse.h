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

typedef struct s_state
{
	char *map_name;
	int	fd;
	t_list *l_map;
	char **map;
	char *n_tex;
	char *s_tex;
	char *w_tex;
	char *e_tex;
	int floor[3];
	int ceiling[3]; 
	int pos_x;
	int pos_y;
	

} t_state;

#endif