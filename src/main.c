/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbank <dbank@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 12:22:29 by dbank         #+#    #+#                 */
/*   Updated: 2025/07/01 17:39:11 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

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

void	calc_movement(t_data *data, float x_inc, float y_inc)
{
	int new_y = (int)(data->player.pos_y + y_inc);
	int new_x = (int)(data->player.pos_x + x_inc);
	if (data->map[new_y][new_x] == '1')
	{
		return;
	}
	data->player.pos_x += x_inc;
	data->player.pos_y += y_inc;
	printf("x: %f, y: %f\n", data->player.pos_x, data->player.pos_y);
}

void move_player(void *param)
{
	t_data *data = (t_data *)param;

	if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_W))
		calc_movement(data, 0, -0.5);
	if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_S))
	   calc_movement(data, 0, 0.5);
	if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_A))
		calc_movement(data, -0.5, 0);
	if (mlx_is_key_down(data->mlx.mlx, MLX_KEY_D))
		calc_movement(data, 0.5, 0);
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
	init_textures(&data, &data.mlx);
	// mlx_key_hook(data.mlx.mlx, key_hook, &data.mlx.mlx);
	// mlx_loop_hook(data.mlx.mlx, raycaster, &data);
	// render_background((int[3]){40, 40, 120}, (int[3]){50, 110, 40}, &data.mlx);
	mlx_loop_hook(data.mlx.mlx, move_player, &data);
	mlx_loop(data.mlx.mlx);
	mlx_terminate(data.mlx.mlx);
	werror("Finished.", &data);
	return 0;
}
