/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:50:17 by showard           #+#    #+#             */
/*   Updated: 2025/07/10 11:50:56 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

static void	put_player_pixel(t_data *data, int pos_x, int pos_y, int radius)
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
                x < data->map_width * MINIMAP_SCALE &&
                y < data->map_height * MINIMAP_SCALE)
                mlx_put_pixel(data->mlx.minimap_image, x, y, 0xFF00D97E);
            offsety++;
        }
        offsetx++;
    }
}

static void	draw_player(t_data *data)
{
    int pos_x;
    int pos_y;
    int radius;

    pos_x = (int)(data->player.pos_x * MINIMAP_SCALE);
    pos_y = (int)(data->player.pos_y * MINIMAP_SCALE);
    radius = MINIMAP_SCALE / 3;
    put_player_pixel(data, pos_x, pos_y, radius);
}

static void	draw_minimap_pixel(t_data *data, int map_i, int map_j, uint32_t color)
{
    int pos_x;
    int pos_y;

    pos_y = 0;
    while (pos_y < MINIMAP_SCALE)
    {
        pos_x = 0;
        while (pos_x < MINIMAP_SCALE)
        {
            mlx_put_pixel(
                data->mlx.minimap_image,
                map_j * MINIMAP_SCALE + pos_x,
                map_i * MINIMAP_SCALE + pos_y,
                color
            );
            pos_x++;
        }
        pos_y++;
    }
}

void	draw_minimap(t_data *data)
{
    int i;
    int j;
    uint32_t color;

    i = 0;
    while (data->map[i] != NULL)
    {
        j = 0;
        while (data->map[i][j] != '\0')
        {
            if (data->map[i][j] == '1')
                color = 0x000000FF;
            else
                color = 0xFFEEEEEE;
            draw_minimap_pixel(data, i, j, color);
            j++;
        }
        i++;
    }
    draw_player(data);
}

// todo:
// render instantly (there's a delay to the minimap showing up)
// minimap hidden behind walls holy fuck i cant figure this out i dont think its z axis
// raycasting FOV