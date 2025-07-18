/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: showard <showard@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 12:22:29 by dbank         #+#    #+#                 */
/*   Updated: 2025/07/18 13:22:59 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

double	set_orientation(char player)
{
	if (player == 'N')
		return (-M_PI / 2);
	else if (player == 'E')
		return (0);
	else if (player == 'S')
		return (M_PI / 2);
	else
		return (M_PI);
}

void	handle_window_resize(t_data *game)
{
	int	width;
	int	height;

	width = game->mlx.mlx->width;
	height = game->mlx.mlx->height;
	if ((width != game->last_w || height != game->last_h)
		&& is_window_size_valid(width, height))
	{
		game->last_w = width;
		game->last_h = height;
		game->minimap_scale = height / 100;
		render_background(game->ceiling, game->floor, game, true);
		raycaster(game, true);
		draw_minimap(game, true);
	}
}

bool	is_window_size_valid(int32_t width, int32_t height)
{
	if (width < 100 || height < 100)
		return (false);
	if (height / 2 < 2)
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	static t_data	data;

	if (argc != 2 || input_check(argv[1], &data) != 1)
	{
		printf("Error\n");
		printf("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	map_init(&data);
	data.mlx.mlx = mlx_init(SCREENSIZE, SCREENSIZE, "Cub3d", true);
	if (!data.mlx.mlx)
	{
		printf("Failed to initialize MLX\n");
		return (1);
	}
	init_textures(&data, &data.mlx);
	render_background(data.ceiling, data.floor, &data, true);
	raycaster(&data, true);
	draw_minimap(&data, true);
	mlx_loop_hook(data.mlx.mlx, loop_hook, &data);
	mlx_loop(data.mlx.mlx);
	mlx_terminate(data.mlx.mlx);
	werror(NULL, &data);
	return (0);
}
