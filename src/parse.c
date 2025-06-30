#include "parse.h"

void	werror(char *error_msg, t_state *state)
{
	free(state->map_name);
	if (state->fd >= 3)
		state->fd = close(state->fd);
	state->map = free_2d(state->map);
	free(state->n_tex);
	free(state->s_tex);
	free(state->w_tex);
	free(state->e_tex);
	ft_putstr_fd("Error\n", 2, NULL);
	ft_putstr_fd(error_msg, 2, NULL);
	exit(EXIT_FAILURE);
}

bool	input_check(char *str, t_state *state)
{
	char	*ext;
	char	*map_name;
	int		i;

	ext = ".cub";
	map_name = str;
	i = 4;
	while (*str != '\0')
	{
		str++;
	}
	while (i >= 0)
	{
		if (*str != ext[i])
			return (false);
		i--;
		str--;
	}
	state->map_name = ft_strjoin("./maps/", map_name);
	return (true);
}

void	init_map(t_state *state)
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

void	print_list(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current)
	{
		printf("%s", (char *)current->content);
		current = current->next;
	}
	// NOT ALLOWED FUNCTION
	printf("\n");
	fflush(stdout);
}

int	count_list(t_list *lst)
{
	t_list	*current;
	int		i;

	i = 0;
	current = lst;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
void	ft_lstdelcontent(void *content)
{
	free(content);
	content = NULL;
}

char	*ft_strdup_nonl(const char *s)
{
	int		length;
	int		i;
	char	*str;

	length = 0;
	i = 0;
	while (s[length] && s[length] != '\n')
		length++;
	str = (char *)malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < length)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**lst_to_2darray(t_state *state)
{
	char	**map;
	int		lines;
	t_list	*current;
	int		i;

	i = 0;
	current = state->l_map;
	lines = count_list(state->l_map);
	map = (char **)malloc((lines + 1) * sizeof(char **));
	if (map == NULL)
		werror("Malloc failure in map initialization\n", state);
	while (current)
	{
		map[i] = ft_strdup_nonl((char *)current->content);
		if (map[i] == NULL)
			werror("Malloc failure in map initialization\n", state);
		current = current->next;
		i++;
	}
	map[i] = NULL;
	ft_lstclear(&state->l_map, ft_lstdelcontent);
	state->l_map = NULL;
	return (map);
}

int	atoi_overflow(const char *nptr, t_state *state)
{
	int		sign;
	long	value;
	int		digit;

	sign = 1;
	value = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = *nptr - '0';
		if (sign == 1 && (value > (INT_MAX - digit) / 10))
			werror("Integer overflow detected.\n", state);
		if (sign == -1 && (-value < (INT_MIN + digit) / 10))
			werror("Integer underflow detected.\n", state);
		value = value * 10 + digit;
		nptr++;
	}
	return (value * sign);
}

void	validate_rgb(char *str, t_state *state, int *colour_arr)
{
	int	i;
	int	counter;
	int	num;

	i = 2;
	counter = 0;
	num = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' || !ft_isdigit(str[i]))
			werror("RGB values incorrectly formatted (e.g., F 220,100,0).\n",
				state);
		num = atoi_overflow(&str[i], state);
		if (num < 0 || num > 255)
			werror("RGB values must be between 0-255\n", state);
		colour_arr[counter] = num;
		while (ft_isdigit(str[i]))
			i++;
		counter++;
		if (counter < 3)
		{
			if (str[i] != ',')
				werror("RGB values incorrectly formatted (e.g., F 220,100,0)\n",
					state);
			i++;
		}
	}
}

char	*copy_path(const char *s, t_state *state)
{
	int		length;
	int		i;
	char	*str;

	length = 0;
	i = 0;
	while (s[length] && s[length] != ' ')
		length++;
	str = (char *)malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < length)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	while (s[i] != '\0')
	{
		if (s[i] != ' ')
			werror("Invalid element line found in file.", state);
		i++;
	}
	return (str);
}

void	init_tex_path(char *map, t_state *state, char **path)
{
	int i;

	i = 0;
	while(map[i] == ' ')
		i++;
	*path = copy_path(&map[i], state);
}

bool	check_element(char *element, t_state *state)
{
	int i;

	i = 0;
	if (element[i] == 'N' && (element[i + 1] == 'O') && state->n_tex == NULL)
		init_tex_path(&element[i + 2], state, &state->n_tex);
	else if (element[i] == 'S' && (element[i + 1] == 'O') && state->s_tex == NULL)
		init_tex_path(&element[i + 2], state, &state->s_tex);
	else if (element[i] == 'W' && (element[i + 1] == 'E') && state->w_tex == NULL)
		init_tex_path(&element[i + 2], state, &state->w_tex);
	else if (element[i] == 'E' && (element[i + 1] == 'A') && state->e_tex == NULL)
		init_tex_path(&element[i + 2], state, &state->e_tex);
	else if (element[i] == 'F' && state->floor[0] == -1)
		validate_rgb(&element[i], state, state->floor);
	else if (element[i] == 'C' && state->ceiling[0] == -1)
		validate_rgb(&element[i], state, state->ceiling);
	else
		return (false);
	return (true);
}
int	validate_elements(char **map, t_state *state)
{
	int i;
	int j;
	int element_count;

	i = 0;
	element_count = 0;
	state->floor[0] = -1;
	state->ceiling[0] = -1;
	while (map[i] != NULL && element_count != 6)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (check_element(&map[i][j], state) == false)
		{
			if (map[i][j] != '\0')
				werror("Invalid element line found in file.", state);
		}
		else
			element_count++;
		i++;
	}
	if (element_count != 6)
		werror("Couldn't find all required elements.", state);
	return (i);
}

void	init_player_pos(t_state *state, char **map)
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

char	**find_start_line(char **map, int start_line)
{
	int	i;
	int	j;

	i = start_line;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != ' ')
			{
				return (&map[i]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void	map_trim(t_state *state, char **start_line)
{
	int		line_count;
	char	**trimmed_map;
	int		i;

	i = 0;
	line_count = 0;
	if (start_line == NULL)
		werror("Reached end of file before finding map start", state);
	while (start_line[line_count] != NULL)
		line_count++;
	trimmed_map = (char **)malloc((line_count + 1) * sizeof(char *));
	if (trimmed_map == NULL)
		werror("Malloc failure", state);
	while (i < line_count)
	{
		trimmed_map[i] = ft_strdup(start_line[i]);
		i++;
	}
	trimmed_map[i] = NULL;
	free_2d(state->map);
	state->map = trimmed_map;
}

int	valid_char(char c)
{
	if (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E')
		return (1);
	return (0);
}

void	validate_chars(t_state *state, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (valid_char(map[i][j]) == 0)
			{
				printf("%s\n", map[i]);
				werror("Invalid character detected in map.", state);
			}
			j++;
		}
		i++;
	}
}

void print_map(t_state *state)
{
	int i;

	i = 0;
	while (state->map[i] != NULL)
	{
		printf("%s\n", state->map[i]);
		i++;
	}
	printf("x: %i y: %i\n", state->pos_x, state->pos_y);
	printf("n: %s\n", state->n_tex);
	printf("n: %s\n", state->s_tex);
	printf("n: %s\n", state->w_tex);
	printf("n: %s\n", state->e_tex);
	printf("R: %i, G: %i, B: %i\n", state->floor[RED], state->floor[GREEN],
		state->floor[BLUE]);
	printf("R: %i, G: %i, B: %i\n", state->ceiling[RED], state->ceiling[GREEN],
		state->ceiling[BLUE]);
}

static void	flood_map(t_state *state, char **map, int x, int y)
{
	if (y < 0 || map[y] == NULL || x < 0 || x >= (int)ft_strlen(map[y]))
    	werror("Map is not closed. Player got out of bounds.", state);
	if (map[y][x] == ' ')
   		werror("Map is not closed. Player touched space.", state);
	if (map[y][x] == '1' || map[y][x] == '.')
		return ;
	map[y][x] = '.';
	flood_map(state, map, x + 1, y);
	flood_map(state, map, x - 1, y);
	flood_map(state, map, x, y + 1);
	flood_map(state, map, x, y - 1);
}

void init_map_bounds(t_state *state, char **map)
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

int	main(int argc, char *argv[])
{
	t_state state;

	ft_bzero(&state, sizeof(t_state));
	if (argc != 2 || input_check(argv[1], &state) != 1)
	{
		printf("Error\n");
		printf("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	map_init(&state);
	werror("Finished.\n", &state);
	return (0);
}