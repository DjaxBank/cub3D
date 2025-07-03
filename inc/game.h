/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:46:47 by dbank             #+#    #+#             */
/*   Updated: 2025/06/25 14:25:09 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdio.h>
# include <math.h>

# define N 0
# define S 1
# define W 2
# define E 3
# define MFACTOR 0.25

typedef struct t_player
{
	double			orientation;
	double			pos_y;
	double			pos_x;
	
}	t_player;

typedef struct t_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*ceiling;
	mlx_image_t		*floor;
	mlx_image_t		**wall;
	mlx_texture_t	*block;
	mlx_texture_t	*tex[4];
	mlx_image_t		*block_image;
	
} t_mlx;

typedef struct t_data
{
	char		**map;
	char		*map_name;
	int	fd;
	t_list *l_map;
	char *n_tex;
	char *s_tex;
	char *w_tex;
	char *e_tex;
	int floor[3];
	int ceiling[3]; 
	int map_width;
	int map_height;
	t_player	player;
	t_mlx 		mlx;
	
} t_data;


void	key_hook(struct mlx_key_data key, void *param);
void	loop_hook(void *param);
void	render_background(const int ceilingc[3], const int floorc[3], t_mlx *mlx);
void	raycaster(t_data *game);
void	fill_image(mlx_image_t *image, uint32_t colour, size_t width, size_t height);

#endif