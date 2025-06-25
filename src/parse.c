#include "parse.h"

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

void map_init(t_state *state)
{
	state->fd = open(state->map_name, O_RDONLY);
	if (state->fd == -1)
		 //

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

	return 0;
}