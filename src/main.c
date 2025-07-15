/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:29 by dbank             #+#    #+#             */
/*   Updated: 2025/07/15 15:07:12 by showard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

static double set_orientation(char player)
{
	if (player == 'N')
		return (-M_PI/2);
	else if (player == 'E')
		return (0);
	else if (player == 'S')
		return (M_PI / 2);
	else
		return (M_PI);
}

static void	init_textures(t_data *data, t_mlx *mlx)
{
	mlx->tex[N] = mlx_load_png(data->n_tex);
	if (mlx->tex[N] == NULL)
		werror("Failure loading NO texture.", data);
	mlx->tex[S] = mlx_load_png(data->s_tex);
	if (mlx->tex[S] == NULL)
		werror("Failure loading SO texture.", data);
	mlx->tex[W] = mlx_load_png(data->w_tex);
	if (mlx->tex[W] == NULL)
		werror("Failure loading WE texture.", data);
	mlx->tex[E] = mlx_load_png(data->e_tex);
	if (mlx->tex[E] == NULL)
		werror("Failure loading EA texture.", data);
}

void collision_check(t_data *game, float new_y, float new_x)
{
	if (game->map[(int)(new_y - 0.1)][(int)(new_x - 0.1)] != '1'
		&& game->map[(int)(new_y - 0.1)][(int)(new_x + 0.1)] != '1' 
		&& game->map[(int)(new_y + 0.1)][(int)(new_x - 0.1)] != '1' 
		&& game->map[(int)(new_y + 0.1)][(int)(new_x + 0.1)] != '1')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	else
	{
		if (game->map[(int)(game->player.pos_y)][(int)(new_x - 0.1)] != '1' 
			&& game->map[(int)(game->player.pos_y)][(int)(new_x + 0.1)] != '1')
			game->player.pos_x = new_x;
		if (game->map[(int)(new_y - 0.1)][(int)(game->player.pos_x )] != '1' 
			&& game->map[(int)(new_y + 0.1)][(int)(game->player.pos_x )] != '1')
			game->player.pos_y = new_y;
	}
}

void handle_window_resize(t_data *game)
{
	int w = game->mlx.mlx->width;
	int h = game->mlx.mlx->height;

	if ((w != game->last_w || h != game->last_h) && is_window_size_valid(w, h))
	{
		game->last_w = w;
		game->last_h = h;
		render_background(game->ceiling, game->floor, game, true);
		raycaster(game, true);
		draw_minimap(game, true);
	}
}

bool is_window_size_valid(int32_t width, int32_t height)
{
	if (width < 100 || height < 100)
		return false;
	if (height / 2 < 2)
		return false;
	return true;
}

int	main(int argc, char *argv[])
{
	static t_data data;
	
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
	data.player.orientation = set_orientation(data.map[(int)data.player.pos_y][(int)data.player.pos_x]);
	render_background(data.ceiling, data.floor, &data, true);
	raycaster(&data, true);
	draw_minimap(&data, true);
	mlx_loop_hook(data.mlx.mlx, loop_hook, &data);
	mlx_loop(data.mlx.mlx);
	mlx_terminate(data.mlx.mlx);
	werror(NULL, &data);
	return 0;
}
