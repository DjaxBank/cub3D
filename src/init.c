/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:45:12 by showard           #+#    #+#             */
/*   Updated: 2025/07/03 16:17:30 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	init_map(t_data *data)
{
	char	*line;
	t_list	*node;

	while (1)
	{
		line = get_next_line(data->fd);
		if (line == NULL)
			break ;
		node = ft_lstnew(line);
		if (node == NULL)
			werror("Malloc failure in map initialization.\n", data);
		ft_lstadd_back(&data->l_map, node);
	}
}

static void	init_player_pos(t_data *data, char **map)
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
				data->player.pos_x = x;
				data->player.pos_y = y;
				counter++;
			}
			x++;
		}
		y++;
	}
	if (counter != 1)
		werror("Invalid player position. There must be one.\n", data);
}

static void	init_map_bounds(t_data *data, char **map)
{
	int	x;
	int	y;
	int	map_chars;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		map_chars = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '1' || map[y][x] == '0' || map[y][x] == 'N'
				|| map[y][x] == 'S' || map[y][x] == 'W' || map[y][x] == 'E')
				map_chars++;
			x++;
		}
		if (map_chars == 0)
			werror("Map line is empty or contains no valid characters.\n",
				data);
		if (x > data->map_width)
			data->map_width = x;
		y++;
	}
	data->map_height = y;
}

void	map_init(t_data *data)
{
	int	counter;

	data->fd = open(data->map_name, O_RDONLY);
	if (data->fd == -1)
		werror("Cannot open map file.\n", data);
	init_map(data);
	data->map = lst_to_2darray(data);
	counter = validate_elements(data->map, data);
	map_trim(data, find_start_line(data->map, counter));
	validate_chars(data, data->map);
	init_player_pos(data, data->map);
	init_map_bounds(data, data->map);
	flood_map(data, data->map, data->player.pos_x, data->player.pos_y);
	free_2d(data->map);
	data->map = lst_to_2darray(data);
	map_trim(data, find_start_line(data->map, counter));
	ft_lstclear(&data->l_map, ft_lstdelcontent);
	data->l_map = NULL;
}
