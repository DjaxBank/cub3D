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
	int map_width;
	int map_height;
	

} t_state;

void	map_trim(t_state *state, char **start_line);
char	*ft_strdup_nonl(const char *s);
int		atoi_overflow(const char *nptr, t_state *state);
char	**lst_to_2darray(t_state *state);
void	werror(char *error_msg, t_state *state);
int		count_list(t_list *lst);
int		validate_elements(char **map, t_state *state);
bool	input_check(char *str, t_state *state);
void	validate_chars(t_state *state, char **map);
char	**find_start_line(char **map, int start_line);
void	flood_map(t_state *state, char **map, int x, int y);
void	map_init(t_state *state);

// debug
void 	print_map(t_state *state);
#endif