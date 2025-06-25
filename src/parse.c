#include "parse.h"

void werror(char *error_msg, t_state *state)
{
	free(state->map_name);
	if (state->fd >= 3)
		state->fd = close(state->fd);
	free_2d(state->map);
	ft_putstr_fd("Error\n", 2, NULL);
	ft_putstr_fd(error_msg, 2, NULL);
	exit(EXIT_FAILURE);
}

bool input_check(char *str, t_state *state)
{
	char *ext;
	char *map_name;
	int i;

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
	char *line;
	t_list *node;

	while (1)
	{
		line = get_next_line(state->fd);
		if (line == NULL)
			break;
		node = ft_lstnew(line);
		if (node == NULL)
			werror("Malloc failure in map initialization.\n", state);
		ft_lstadd_back(&state->l_map, node);
	}
}

void	print_list(t_list *lst)
{
	t_list *current;

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
	t_list *current;
	int i;

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

char **lst_to_2darray(t_state *state)
{
	char **map;
	int lines;
	t_list *current;
	int i;

	i = 0;
	current = state->l_map;
	lines = count_list(state->l_map);
	map = (char **)malloc((lines + 1) * sizeof(char **));
	if (map == NULL)
		werror("Malloc failure in map initialization\n", state);
	while (current)
	{
		map[i] = ft_strdup((char *)current->content);
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

void	validate_elements(char **map, t_state *state)
{
	int i;

	i = 0;
	while (map[i] && map[i][0] != 'N')
        i++;
    if (!map[i] || ft_strncmp(map[i++], "NO ./", 5) != 0)
        werror("Invalid map element. North must be NO <path>\n", state);
    if (!map[i] || ft_strncmp(map[i++], "SO ./", 5) != 0)
        werror("Invalid map element. South must be SO <path>\n", state);
    if (!map[i] || ft_strncmp(map[i++], "WE ./", 5) != 0)
        werror("Invalid map element. West must be WE <path>\n", state);
    if (!map[i] || ft_strncmp(map[i++], "EA ./", 5) != 0)
        werror("Invalid map element. East must be EA <path>\n", state);
    i++;
    if (!map[i] || ft_strncmp(map[i++], "F ", 2) != 0)
        werror("Invalid map element. Floor colour must be F <RGB>\n", state);
    if (!map[i] || ft_strncmp(map[i++], "C ", 2) != 0)
        werror("Invalid map element. Ceiling colour must be C <RGB>\n", state);

}

void map_init(t_state *state)
{
	state->fd = open(state->map_name, O_RDONLY);
	if (state->fd == -1)
		werror("Cannot open map file.\n", state);
	init_map(state);
	state->map = lst_to_2darray(state);
	validate_elements(state->map, state);
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
	return 0;
}