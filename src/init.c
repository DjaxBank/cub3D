#include "parse.h"

static void	init_map(t_state *state)
{
	char	*line;
	t_list	*node;

	while (1)
	{
		line = get_next_line(state->fd);
		if (line == NULL)
			break ;
		node = ft_lstnew(line);
		if (node == NULL)
			werror("Malloc failure in map initialization.\n", state);
		ft_lstadd_back(&state->l_map, node);
	}
}

static void	init_player_pos(t_state *state, char **map)
{
	int	x;
	int	y;
	int	counter;

	y = 0;
	counter = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W'
				|| map[y][x] == 'E')
			{
				state->pos_x = x;
				state->pos_y = y;
				counter++;
			}
			x++;
		}
		y++;
	}
	if (counter != 1)
		werror("Invalid player position. There must be one. (e.g. N, S, W, or E)\n", state);
}

static void init_map_bounds(t_state *state, char **map)
{
	int x;
	int y;
	int map_chars;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		map_chars = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '1' || map[y][x] == '0' || map[y][x] == 'N' ||
				map[y][x] == 'S' || map[y][x] == 'W' || map[y][x] == 'E')
			{
				map_chars++;
			}
			x++;
		}
		if (map_chars == 0)
			werror("Map line is empty or contains no valid characters.\n", state);
		if (x > state->map_width)
			state->map_width = x;
		y++;
	}
	state->map_height = y;
}

void	map_init(t_state *state)
{
	int	counter;

	state->fd = open(state->map_name, O_RDONLY);
	if (state->fd == -1)
		werror("Cannot open map file.\n", state);
	init_map(state);
	state->map = lst_to_2darray(state);
	counter = validate_elements(state->map, state);
	map_trim(state, find_start_line(state->map, counter));
	validate_chars(state, state->map);
	init_player_pos(state, state->map);
	init_map_bounds(state, state->map);
	flood_map(state, state->map, state->pos_x, state->pos_y);
	print_map(state);
}