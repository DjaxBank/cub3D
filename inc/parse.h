/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: showard <showard@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 15:48:50 by showard       #+#    #+#                 */
/*   Updated: 2025/06/30 16:20:01 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define RED 0
# define GREEN 1
# define BLUE 2

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_data
{
	char	*map_name;
	int		fd;
	t_list	*l_map;
	char	**map;
	char	*n_tex;
	char	*s_tex;
	char	*w_tex;
	char	*e_tex;
	int		floor[3];
	int		ceiling[3];
	int		pos_x;
	int		pos_y;
	int		map_width;
	int		map_height;

}			t_data;

void		map_trim(t_data *data, char **start_line);
char		*ft_strdup_nonl(const char *s);
int			atoi_overflow(const char *nptr, t_data *data);
char		**lst_to_2darray(t_data *data);
void		werror(char *error_msg, t_data *data);
int			count_list(t_list *lst);
int			validate_elements(char **map, t_data *data);
bool		input_check(char *str, t_data *data);
void		validate_chars(t_data *data, char **map);
char		**find_start_line(char **map, int start_line);
void		flood_map(t_data *data, char **map, int x, int y);
void		map_init(t_data *data);

// debug
void		print_map(t_data *data);
#endif