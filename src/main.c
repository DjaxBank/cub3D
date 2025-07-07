/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:29 by dbank             #+#    #+#             */
/*   Updated: 2025/07/07 14:40:28 by showard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

double set_orientation(char player)
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

void	init_textures(t_data *data, t_mlx *mlx)
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

void loop_hook(void *param)
{
    t_data *game = (t_data *)param;

    if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_W))
    {
        float new_y = game->player.pos_y + sin(game->player.orientation) / 20;
    	float new_x = game->player.pos_x + cos(game->player.orientation) / 20;
       	collision_check(game, new_y, new_x);
    }
    if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_S))
    {
        float new_y = game->player.pos_y - sin(game->player.orientation) / 20;
        float new_x = game->player.pos_x - cos(game->player.orientation) / 20;
		collision_check(game, new_y, new_x);
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_A))
		game->player.orientation -= 0.05;
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_D))
		game->player.orientation += 0.05;
	raycaster(game);
	fill_image(game->mlx.minimap_image, 0xFF000000, game->map_width * MINIMAP_SCALE, game->map_height * MINIMAP_SCALE);
    draw_minimap(game);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	
	ft_bzero(&data, sizeof(t_data));
	if (argc != 2 || input_check(argv[1], &data) != 1)
	{
		printf("Error\n");
		printf("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	map_init(&data);
	data.mlx.block = mlx_load_png("textures/block.png");
	data.mlx.mlx = mlx_init(800, 800, "Cub3d", false);
	data.mlx.minimap_image = mlx_new_image(data.mlx.mlx, data.map_width * MINIMAP_SCALE, data.map_height * MINIMAP_SCALE);
	if (!data.mlx.minimap_image)
        werror("Failed to create minimap image", &data);
	mlx_image_to_window(data.mlx.mlx, data.mlx.minimap_image, 10, 10);
	mlx_set_instance_depth(data.mlx.minimap_image->instances, 100);
	data.player.orientation = set_orientation(data.map[(int)data.player.pos_y][(int)data.player.pos_x]);
	// i didn't rip out all of the key hook functions yet.
	// mlx_key_hook(data.mlx.mlx, key_hook, &data);
	mlx_loop_hook(data.mlx.mlx, loop_hook, &data);
	render_background(data.ceiling, data.floor, &data.mlx);
	raycaster(&data);
	mlx_loop(data.mlx.mlx);
	mlx_terminate(data.mlx.mlx);
	werror("Finished.", &data);
	return 0;
}
