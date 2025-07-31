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
# include <math.h>
# include <stdio.h>
# define VERTICAL 1
# define HORIZONTAL 0
# define N 0
# define S 1
# define W 2
# define E 3
# define MFACTOR 0.25
# define SCREENSIZE 1250

typedef struct s_wall
{
	mlx_image_t		*wall;
	mlx_texture_t	*tex;
	int				x;
	int				y;
	int				size;
	size_t			texture_x;
	double			step;
	char			content;
	double			tex_pos;
	int				max_y;
}					t_wall;

typedef struct t_ray
{
	int				y;
	int				x;
	double			hit_x;
	double			hit_y;
	double			raydir_x;
	double			raydir_y;
	double			deltax;
	double			deltay;
	double			sidedistx;
	double			sidedisty;
	double			stepx;
	double			stepy;
	double			angle;
	double			distance;
	double			pos;
	int				side;
	bool			hit_door;
	size_t			*count;
}					t_ray;
typedef struct t_player
{
	double			orientation;
	double			pos_y;
	double			pos_x;

}					t_player;

typedef struct t_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*ceiling;
	mlx_image_t		*floor;
	mlx_image_t		*wall;
	mlx_texture_t	*tex[4];
	mlx_texture_t	*tex2[4];
	mlx_texture_t	*door;
	mlx_image_t		*open_doors;
	mlx_image_t		*minimap_image;

}					t_mlx;

typedef struct t_data
{
	char			**map;
	char			*map_name;
	int				fd;
	t_list			*l_map;
	char			*n_tex;
	char			*s_tex;
	char			*w_tex;
	char			*e_tex;
	int				floor[3];
	int				ceiling[3];
	int				map_width;
	int				map_height;
	t_player		player;
	t_mlx			mlx;
	int				minimap_scale;
	bool			resizing;
	bool			mouse_enabled;
	int				last_w;
	int				last_h;
	bool			rtorch;
	bool			btorch;
	double			fov;
	int32_t			last_mouse_x;
	int32_t			last_mouse_y;

}					t_data;

void				key_hook(struct mlx_key_data key, void *param);
void				render_background(const int ceilingc[3],
						const int floorc[3], t_data *data, bool force_recreate);
void				raycaster(t_data *game, bool force_recreate);
void				fill_image(mlx_image_t *image, uint32_t colour,
						size_t width, size_t height);
void				draw_minimap(t_data *d, bool force_recreate);
void				put_wall(t_data *game, t_ray ray, t_wall wall,
						mlx_image_t *image);
bool				is_window_size_valid(int32_t width, int32_t height);
void				werror(char *error_msg, t_data *data);
void				loop_hook(void *game);
void				handle_window_resize(t_data *game);
void				init_textures(t_data *data, t_mlx *mlx);
void				draw_minimap_fov(t_data *data);
void				open_door(t_data *game);
void				init_ray(t_data *game, t_ray *ray);
double				set_orientation(char player);
void				keypress(t_data *game);
mlx_texture_t		*choose_image(t_data *game, t_ray ray);
void				mouse_hook(mouse_key_t button, action_t action,
						modifier_key_t mods, void *param);
void				key_hook(struct mlx_key_data key, void *game);
void				render_door(t_data *game, t_ray ray);
void				init_wall_vars(size_t *count, t_ray *ray);
void				torch_check(t_data *data, t_mlx *mlx);
void				collision_check(t_data *game, float new_y, float new_x);
void				handle_key_movement(t_data *game, double *new_y,
						double *new_x);
int					check_stuff(int32_t mouse[2], t_data *data);

#endif