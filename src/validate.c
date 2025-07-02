/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:48:39 by showard           #+#    #+#             */
/*   Updated: 2025/07/02 21:05:15 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	input_check(char *str, t_data *data)
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
	data->map_name = ft_strjoin("./maps/", map_name);
	return (true);
}

static int	valid_char(char c)
{
	if (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E')
		return (1);
	return (0);
}

void	validate_chars(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (valid_char(map[i][j]) == 0)
			{
				printf("%s\n", map[i]);
				werror("Invalid character detected in map.", data);
			}
			j++;
		}
		i++;
	}
}

void	flood_map(t_data *data, char **map, int x, int y)
{
	if (y < 0 || map[y] == NULL || x < 0 || x >= (int)ft_strlen(map[y]))
		werror("Map is not closed. Player got out of bounds.", data);
	if (map[y][x] == ' ')
		werror("Map is not closed. Player touched space.", data);
	if (map[y][x] == '1' || map[y][x] == '.')
		return ;
	map[y][x] = '.';
	flood_map(data, map, x + 1, y);
	flood_map(data, map, x - 1, y);
	flood_map(data, map, x, y + 1);
	flood_map(data, map, x, y - 1);
}
