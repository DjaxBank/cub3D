/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:29 by dbank             #+#    #+#             */
/*   Updated: 2025/07/25 14:08:26 by dbank            ###   ########.fr       */
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
	if ((game->mlx.mlx->width != game->last_w
			|| game->mlx.mlx->height != game->last_h)
		&& is_window_size_valid(game->mlx.mlx->width, game->mlx.mlx->height))
	{
		game->last_w = game->mlx.mlx->width;
		game->last_h = game->mlx.mlx->height;
		game->minimap_scale = game->mlx.mlx->height / 100;
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

void	first_run(t_data *data)
{
	render_background(data->ceiling, data->floor, data, true);
	raycaster(data, true);
	draw_minimap(data, true);
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
	data.fov = 60 * M_PI / 180.0;
	map_init(&data);
	init_textures(&data, &data.mlx);
	data.mlx.mlx = mlx_init(SCREENSIZE, SCREENSIZE, "Cub3d", true);
	if (!data.mlx.mlx)
		werror("Failed to initialize MLX", &data);
	mlx_set_cursor_mode(data.mlx.mlx, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(data.mlx.mlx, mousemovement, &data);
	mlx_loop_hook(data.mlx.mlx, loop_hook, &data);
	mlx_key_hook(data.mlx.mlx, key_hook, &data);
	mlx_mouse_hook(data.mlx.mlx, mouse_hook, &data);
	data.toggle = true;
	mlx_loop(data.mlx.mlx);
	mlx_terminate(data.mlx.mlx);
	werror(NULL, &data);
	return (0);
}
