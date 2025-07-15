/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:50:17 by showard           #+#    #+#             */
/*   Updated: 2025/07/15 14:06:34 by showard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

void	put_player_pixel(t_data *data, int pos_x, int pos_y, int radius)
{
    int offsetx;
    int offsety;
    int x;
    int y;

    offsetx = -radius;
    while (offsetx <= radius)
    {
        offsety = -radius;
        while (offsety <= radius)
        {
            x = pos_x + offsetx;
            y = pos_y + offsety;
            if (x >= 0 && y >= 0 &&
                x < data->map_width * data->minimap_scale &&
                y < data->map_height * data->minimap_scale)
            {
                mlx_put_pixel(data->mlx.minimap_image, x, y, 0xFF00D97E);
            }
            offsety++;
        }
        offsetx++;
    }
}

void	draw_player(t_data *data)
{
    int pos_x;
    int pos_y;
    int radius;

    pos_x = (int)(data->player.pos_x * data->minimap_scale);
    pos_y = (int)(data->player.pos_y * data->minimap_scale);
    radius = data->minimap_scale / 3;
    put_player_pixel(data, pos_x, pos_y, radius);
}

void	draw_minimap_pixel(t_data *data, int map_i, int map_j, uint32_t color)
{
    int pos_x;
    int pos_y;
    int px;
    int py;
    
    pos_y = 0;
    while (pos_y < data->minimap_scale)
    {
        pos_x = 0;
        while (pos_x < data->minimap_scale)
        {
            px = map_j * data->minimap_scale + pos_x;
            py = map_i * data->minimap_scale + pos_y;
            mlx_put_pixel(data->mlx.minimap_image, px, py, color);
            pos_x++;
        }
        pos_y++;
    }
}

static void	draw_minimap_ray(t_data *data, double angle, double max_distance, uint32_t color)
{
    double x;
    double y;
    double distance;
    int px;
    int py;

    x = data->player.pos_x;
    y = data->player.pos_y;
    distance = 0.0;
    while (distance < max_distance)
    {
        if (data->map[(int)y][(int)x] == '1')
            break;
        px = (int)(x * data->minimap_scale);
        py = (int)(y * data->minimap_scale);
        if (px >= 0 && py >= 0 &&
            px < data->map_width * data->minimap_scale &&
            py < data->map_height * data->minimap_scale)
        {
            mlx_put_pixel(data->mlx.minimap_image, px, py, color);
        }
        x += cos(angle) * 0.05;
        y += sin(angle) * 0.05;
        distance += 0.05;
    }
}

void	draw_minimap_fov(t_data *data)
{
    int i;
    double fov;
    double start_angle;
    double ray_angle;
    double max_distance;

    i = 0;
    fov = 60.0 * M_PI / 180.0;
    start_angle = data->player.orientation - fov / 2.0;
    max_distance = 100.0;
    while (i < 120)
    {
        ray_angle = start_angle + (fov * i) / (120 - 1);
        draw_minimap_ray(data, ray_angle, max_distance, 0xFF00D97E);
        i++;
    }
}

void draw_minimap(t_data *data, bool force_recreate)
{
    int i;
    int j;
    uint32_t color;

    printf("d\n");
     if (!is_window_size_valid(data->mlx.mlx->width, data->mlx.mlx->height))
        return;
    if (force_recreate || !data->mlx.minimap_image)
    {
        if (data->mlx.minimap_image)
            mlx_delete_image(data->mlx.mlx, data->mlx.minimap_image);
        data->mlx.minimap_image = mlx_new_image(data->mlx.mlx, 
            data->map_width * data->minimap_scale, 
            data->map_height * data->minimap_scale);
        if (!data->mlx.minimap_image)
        {
            printf("Failed to create minimap image\n");
            return;
        }
        mlx_image_to_window(data->mlx.mlx, data->mlx.minimap_image, 10, 10);
        mlx_set_instance_depth(data->mlx.minimap_image->instances, 2);
    }
    printf("e\n");
    if (!data->mlx.minimap_image)
        return;
    fill_image(data->mlx.minimap_image, 0xFF000000, data->map_width * data->minimap_scale, data->map_height * data->minimap_scale);
    i = 0;
    while (data->map[i] != NULL)
    {
        j = 0;
        while (data->map[i][j] != '\0')
        {
            color = 0xFFEEEEEE;
            if (data->map[i][j] == '1')
                color = 0x000000FF;
            draw_minimap_pixel(data, i, j, color);
            j++;
        }
        i++;
    }
    draw_minimap_fov(data);
    draw_player(data);
    printf("f\n");
}

// todo:
// minimap is hidden behind walls again. my quick fix broke the map rendering (background seemed to render above walls)