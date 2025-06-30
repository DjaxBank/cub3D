/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: showard <showard@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 15:44:41 by showard       #+#    #+#                 */
/*   Updated: 2025/06/30 15:52:47 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	werror(char *error_msg, t_data *data)
{
	free(data->map_name);
	if (data->fd >= 3)
		data->fd = close(data->fd);
	data->map = free_2d(data->map);
	free(data->n_tex);
	free(data->s_tex);
	free(data->w_tex);
	free(data->e_tex);
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
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc != 2 || input_check(argv[1], &data) != 1)
	{
		printf("Error\n");
		printf("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	map_init(&data);
	werror("Finished.\n", &data);
	return (0);
}

// to do:
// fix everything to be t_data