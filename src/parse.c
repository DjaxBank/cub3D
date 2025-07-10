/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:44:41 by showard           #+#    #+#             */
/*   Updated: 2025/07/10 11:52:38 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "game.h"

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
	if (error_msg)
	{
		ft_putstr_fd("Error\n", 2, NULL);
		ft_putstr_fd(error_msg, 2, NULL);
		exit(EXIT_FAILURE);
	}
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

// to do:
// fix everything to be t_data
