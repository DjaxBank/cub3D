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

// to do:
// fix everything to be s_data