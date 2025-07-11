/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:29 by dbank             #+#    #+#             */
/*   Updated: 2025/07/11 14:44:54 by dbank            ###   ########.fr       */
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

static void collision_check(t_data *game, float new_y, float new_x)
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

static void loop_hook(void *param)
{
	#include <unistd.h>
    t_data *game = (t_data *)param;
	const double save[3] = {game->player.pos_y, game->player.pos_x, game->player.orientation};

	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_ESCAPE))
	return (mlx_close_window(game->mlx.mlx));
    if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_W))
    {
		double new_y = game->player.pos_y + sin(game->player.orientation) / 20 * (game->mlx.mlx->delta_time * 60);
    	double new_x = game->player.pos_x + cos(game->player.orientation) / 20 * (game->mlx.mlx->delta_time * 60);
		collision_check(game, new_y, new_x);
    }
    if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_S))
    {
		double new_y = game->player.pos_y - sin(game->player.orientation) / 20 * (game->mlx.mlx->delta_time * 60);
        double new_x = game->player.pos_x - cos(game->player.orientation) / 20 * (game->mlx.mlx->delta_time * 60);
		collision_check(game, new_y, new_x);
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_A))
	game->player.orientation -= 0.05 * (game->mlx.mlx->delta_time * 60);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_D))
	game->player.orientation += 0.05 * (game->mlx.mlx->delta_time * 60);
	if (save[0] != game->player.pos_y || save[1] != game->player.pos_x || save[2] != game->player.orientation )
	{
		raycaster(game);
		draw_minimap(game);
	}
}

static void resize_hook(int32_t width, int32_t height, void *param)
{
	t_data *game = (t_data *)param;
	int new_scale;

	if (width < height)
		new_scale = width / 100;
	else
		new_scale = height / 100;
	if (new_scale < 1)
		new_scale = 1;
	game->minimap_scale = new_scale;
	if (game->mlx.minimap_image)
		mlx_delete_image(game->mlx.mlx, game->mlx.minimap_image);
	game->mlx.minimap_image = mlx_new_image(game->mlx.mlx, game->map_width * new_scale, game->map_height * new_scale);
	if (!game->mlx.minimap_image)
		werror("Failed to create minimap image", game);
	render_background(game->ceiling, game->floor, &game->mlx);
	raycaster(game);
	draw_minimap(game);
	mlx_image_to_window(game->mlx.mlx, game->mlx.minimap_image, 10, 10);
	mlx_set_instance_depth(game->mlx.minimap_image->instances, 100);
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
    init_textures(&data, &data.mlx);
    data.mlx.mlx = mlx_init(SCREENSIZE, SCREENSIZE, "Cub3d", true);
    data.mlx.minimap_image = mlx_new_image(data.mlx.mlx, data.map_width * data.minimap_scale, data.map_height * data.minimap_scale);
    if (!data.mlx.minimap_image)
        werror("Failed to create minimap image", &data);
    data.player.orientation = set_orientation(data.map[(int)data.player.pos_y][(int)data.player.pos_x]);
	mlx_resize_hook(data.mlx.mlx, resize_hook, &data);
    mlx_loop_hook(data.mlx.mlx, loop_hook, &data);
    render_background(data.ceiling, data.floor, &data.mlx);
    raycaster(&data);
    mlx_loop(data.mlx.mlx);
    mlx_terminate(data.mlx.mlx);
    werror(NULL, &data);
    return 0;
}
